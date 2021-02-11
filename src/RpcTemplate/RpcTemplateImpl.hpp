#pragma once
#include <cppcoro/sync_wait.hpp>
#include "TrivialValue.hpp"
#include "Arg/IntArgImpl.hpp"
#include "Arg/EnumArgImpl.hpp"
#include "Arg/JsonRawArgImpl.hpp"
#include "Arg/StringArgImpl.hpp"
#include "Arg/BoolArgImpl.hpp"
#include "Arg/FlattedStringArrayArgImpl.hpp"
#include "Responder/NormalResultResponderImpl.hpp"
#include "Responder/EventResponderImpl.hpp"
#include "../spawn.hpp"
namespace ubot
{
	template<typename TResponder, typename... TArgs, typename THandler, size_t... Indices>
	void SetNativeHandlerImpl(ubot::JsonRpc& rpc, 
		std::string_view name, 
		THandler handler,
		std::index_sequence<Indices...>)
	{
		rpc.SetHandler(name, [handler](rapidjson::Value&& params, TWriter& writer) -> cppcoro::task<>
			{
				size_t nArgs = params.IsArray() ? params.Size() : 0;
				if constexpr (std::is_void_v<typename TResponder::NativeTypeEx>)
				{
					static_assert(std::is_convertible_v<THandler, std::function<typename TResponder::NativeType(typename TArgs::NativeType...)>>, "invalid handler");
					if constexpr (std::is_void_v<typename TResponder::NativeType>)
					{
						handler((ArgImpl<TArgs>::TempRead(Indices < nArgs ? &(params.GetArray()[Indices]) : nullptr).get())...);
						ResponderImpl<TResponder>::Respond(writer);
					}
					else
					{
						auto result = handler((ArgImpl<TArgs>::TempRead(Indices < nArgs ? &(params.GetArray()[Indices]) : nullptr).get())...);
						ResponderImpl<TResponder>::Respond(writer, result);
					}
				} 
				else 
				{
					static_assert(std::is_convertible_v<THandler, std::function<typename TResponder::NativeType(typename TArgs::NativeType..., typename TResponder::NativeTypeEx)>>, "invalid handler");
					auto resultEx = ResponderImpl<TResponder>::MakeResultEx();
					if constexpr (std::is_void_v<typename TResponder::NativeType>)
					{
						handler((ArgImpl<TArgs>::TempRead(Indices < nArgs ? &(params.GetArray()[Indices]) : nullptr).get())..., resultEx.get());
						ResponderImpl<TResponder>::Respond(writer, resultEx.get());
					}
					else
					{
						auto result = handler((ArgImpl<TArgs>::TempRead(Indices < nArgs ? &(params.GetArray()[Indices]) : nullptr).get())..., resultEx.get());
						ResponderImpl<TResponder>::Respond(writer, result, resultEx.get());
					}
				}
				co_return;
			});
	}

	template<typename TResponder, typename... TArgs, typename THandler>
	void SetNativeHandler(ubot::JsonRpc& rpc,
		std::string_view name,
		THandler handler)
	{
		SetNativeHandlerImpl<TResponder, TArgs...>(rpc, name, handler, std::index_sequence_for<TArgs...>{});
	}


	struct AsyncReturnInfo
	{
		std::experimental::coroutine_handle<> handle;
		TWriter* writer;
	};

	template<typename... TArgs, typename THandler, size_t... Indices>
	void SetNativeAsyncHandlerImpl(ubot::JsonRpc& rpc,
		std::string_view name,
		THandler handler,
		std::index_sequence<Indices...>)
	{
		static_assert(std::is_convertible_v<THandler, std::function<void(typename TArgs::NativeType..., void* async)>>, "invalid handler");
		rpc.SetHandler(name, [handler](rapidjson::Value&& params, TWriter& writer) -> cppcoro::task<>
			{
				struct awaiter
				{
					using TStoredArgs = std::tuple<decltype(ArgImpl<TArgs>::TempRead(nullptr))...>;
					AsyncReturnInfo info;
					THandler storedHandler;
					TStoredArgs storedArgs;
					awaiter(TWriter* _storedWriter, THandler _storedHandler, TStoredArgs&& _storedArgs)
						:storedHandler(_storedHandler), storedArgs(std::move(_storedArgs))
					{
						info.writer = _storedWriter;
					}
					bool await_ready() noexcept
					{
						return false;
					}
					void await_suspend(std::experimental::coroutine_handle<> handle)
					{
						info.handle = handle;
						storedHandler(std::get<Indices>(storedArgs).get()..., &info);
					}
					void await_resume() noexcept
					{
					}
				};
				size_t nArgs = params.IsArray() ? params.Size() : 0;
				co_await awaiter(&writer, handler, std::make_tuple(ArgImpl<TArgs>::TempRead(Indices < nArgs ? &(params.GetArray()[Indices]) : nullptr)...));
			});
	}

	template<typename... TArgs, typename THandler>
	void SetNativeAsyncHandler(ubot::JsonRpc& rpc,
		std::string_view name,
		THandler handler)
	{
		SetNativeAsyncHandlerImpl<TArgs...>(rpc, name, handler, std::index_sequence_for<TArgs...>{});
	}

	template<typename TBuilder, std::enable_if_t<std::is_convertible_v<TBuilder, std::function<void(TWriter& writer)>>, int> = 0>
	void AsyncReturn(void* async, TBuilder builder)
	{
		auto info = static_cast<AsyncReturnInfo*>(async);
		builder(*info->writer);
		if (info->handle)
		{
			info->handle.resume();
		}
	}

	template<typename TResult, typename... TArgs>
	typename auto CallFromNative(ubot::JsonRpc& rpc,
		std::string_view name,
		typename TArgs::NativeType... args)
	{
		auto raw = cppcoro::sync_wait(rpc.Call(name, [&](TWriter& writer)
			{
				writer.StartArray();
				[[maybe_unused]] int dummy[] = {
					(ArgImpl<TArgs>::Write(writer, args), 0)...
				};
				writer.EndArray();
			}, true));
		if constexpr (std::is_void_v<TResult>)
		{
			return;
		}
		else
		{
			return ArgImpl<TResult>::PempRead(raw.Error.has_value() ? nullptr : &raw.Result);
		}
	}

	template<typename TResult, 
		typename... TArgs, 
		typename THandler>
	spawn_t CallFromNativeAsync(ubot::JsonRpc& rpc,
		std::string_view name,
		typename TArgs::NativeType... args, 
		typename THandler handle)
	{
		JsonRpcResult raw = co_await rpc.Call(name, [&](TWriter& writer)
			{
				writer.StartArray();
				[[maybe_unused]] int dummy[] = {
					(ArgImpl<TArgs>::Write(writer, args), 0)...
				};
				writer.EndArray();
			});
		if constexpr (std::is_void_v<TResult>)
		{
			static_assert(std::is_convertible_v<THandler, std::function<void()>>, "invalid handler");
			handle();
		}
		else
		{
			static_assert(std::is_convertible_v<THandler, std::function<void(typename TResult::NativeType result)>>, "invalid handler");
			auto nativeResult = ArgImpl<TResult>::TempRead(raw.Error.has_value() ? nullptr : &raw.Result);
			handle(nativeResult.get());
		}
	}
}