#pragma once
#include "RpcTemplate/TrivialValue.hpp"
#include "RpcTemplate/IntArg.hpp"
#include "RpcTemplate/EnumArg.hpp"
#include "RpcTemplate/JsonRawArg.hpp"
#include "RpcTemplate/StringArg.hpp"
#include "RpcTemplate/BoolArg.hpp"
#include "RpcTemplate/FlattedStringArrayArg.hpp"
#include "RpcTemplate/NormalResultResponder.hpp"
namespace ubot
{
	template<typename TResponder, typename... TArgs, typename THandler, size_t... Indices>
	void SetNativeHandlerImpl(ubot::JsonRpc& rpc, 
		const std::string& name, 
		THandler handler,
		std::index_sequence<Indices...>)
	{
		rpc.SetHandler(name, [handler](rapidjson::Value&& params, TWriter& writer)
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
			});
	}

	template<typename TResponder, typename... TArgs, typename THandler>
	void SetNativeHandler(ubot::JsonRpc& rpc,
		const std::string& name,
		THandler handler)
	{
		SetNativeHandlerImpl<TResponder, TArgs...>(rpc, name, handler, std::index_sequence_for<TArgs...>{});
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