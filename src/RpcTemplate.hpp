#pragma once
#include "RpcTemplate/TrivialValue.hpp"
#include "RpcTemplate/IntArg.hpp"
#include "RpcTemplate/EnumArg.hpp"
#include "RpcTemplate/JsonRawArg.hpp"
#include "RpcTemplate/StringArg.hpp"
#include "RpcTemplate/BoolArg.hpp"
#include "RpcTemplate/FlattedStringArrayArg.hpp"
#include "RpcTemplate/NormalResultResponder.hpp"
#include "RpcTemplate/EventRespond.hpp"
namespace ubot
{
	template<typename TResponder, typename... TArgs, typename THandler, size_t... Indices>
	void SetNativeHandlerImpl(ubot::JsonRpc& rpc, 
		const std::string& name, 
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
						handler((TArgs::TempRead(Indices < nArgs ? &(params.GetArray()[Indices]) : nullptr).get())...);
						TResponder::Respond(writer);
					}
					else
					{
						auto result = handler((TArgs::TempRead(Indices < nArgs ? &(params.GetArray()[Indices]) : nullptr).get())...);
						TResponder::Respond(writer, result);
					}
				} 
				else 
				{
					static_assert(std::is_convertible_v<THandler, std::function<typename TResponder::NativeType(typename TArgs::NativeType..., typename TResponder::NativeTypeEx)>>, "invalid handler");
					auto resultEx = TResponder::MakeResultEx();
					if constexpr (std::is_void_v<typename TResponder::NativeType>)
					{
						handler((TArgs::TempRead(Indices < nArgs ? &(params.GetArray()[Indices]) : nullptr).get())..., resultEx.get());
						TResponder::Respond(writer, resultEx.get());
					}
					else
					{
						auto result = handler((TArgs::TempRead(Indices < nArgs ? &(params.GetArray()[Indices]) : nullptr).get())..., resultEx.get());
						TResponder::Respond(writer, result, resultEx.get());
					}
				}
				co_return;
			});
	}

	template<typename TResponder, typename... TArgs, typename THandler>
	void SetNativeHandler(ubot::JsonRpc& rpc,
		const std::string& name,
		THandler handler)
	{
		SetNativeHandlerImpl<TResponder, TArgs...>(rpc, name, handler, std::index_sequence_for<TArgs...>{});
	}

	template<typename... TArgs, typename THandler, size_t... Indices>
	void SetNativeAsyncHandlerImpl(ubot::JsonRpc& rpc,
		const std::string& name,
		THandler handler,
		std::index_sequence<Indices...>)
	{
		static_assert(std::is_convertible_v<THandler, std::function<void(typename TArgs::NativeType..., void* async_0, void* async_1)>>, "invalid handler");
		rpc.SetHandler(name, [handler](rapidjson::Value&& params, TWriter& writer) -> cppcoro::task<>
			{
				struct awaiter
				{
					using TStoredArgs = std::tuple<decltype(TArgs::TempRead(nullptr))...>;
					TWriter* storedWriter;
					THandler storedHandler;
					TStoredArgs storedArgs;
					awaiter(TWriter* _storedWriter, THandler _storedHandler, TStoredArgs&& _storedArgs)
						:storedWriter(_storedWriter), storedHandler(_storedHandler), storedArgs(std::move(_storedArgs))
					{
					}
					bool await_ready() noexcept
					{
						return false;
					}
					void await_suspend(std::experimental::coroutine_handle<> handle)
					{
						storedHandler(std::get<Indices>(storedArgs).get()..., handle.address(), storedWriter);
					}
					void await_resume() noexcept
					{
					}
				};
				size_t nArgs = params.IsArray() ? params.Size() : 0;
				co_await awaiter(&writer, handler, std::make_tuple(TArgs::TempRead(Indices < nArgs ? &(params.GetArray()[Indices]) : nullptr)...));
			});
	}

	template<typename... TArgs, typename THandler>
	void SetNativeAsyncHandler(ubot::JsonRpc& rpc,
		const std::string& name,
		THandler handler)
	{
		SetNativeAsyncHandlerImpl<TArgs...>(rpc, name, handler, std::index_sequence_for<TArgs...>{});
	}

	template<typename TBuilder>
	void AsyncReturn(void* async_0, void* async_1, TBuilder builder)
	{
		static_assert(std::is_convertible_v<TBuilder, std::function<void(TWriter& writer)>>, "invalid builder");
		builder(*static_cast<TWriter*>(async_1));
		std::experimental::coroutine_handle<>::from_address(async_0).resume();
	}

	template<typename TResult, typename... TArgs>
	typename auto CallFromNative(ubot::JsonRpc& rpc,
		const std::string& name,
		typename TArgs::NativeType... args)
	{
		auto raw = rpc.Call(name, [&](TWriter& writer)
			{
				writer.StartArray();
				[[maybe_unused]] int dummy[] = {
					(TArgs::Write(writer, args), 0)...
				};
				writer.EndArray();
			});
		if constexpr (std::is_void_v<TResult>)
		{
			return;
		}
		else
		{
			return TResult::PempRead(raw.Error.has_value() ? nullptr : &raw.Result);
		}
	}
}