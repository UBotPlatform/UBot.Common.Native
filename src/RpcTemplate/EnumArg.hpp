#pragma once
#include "TrivialValue.hpp"
#include "JsonRpc.h"
namespace ubot
{
	template<typename T>
	struct EnumArg
	{
		using NativeType = T;
		static void Write(TWriter& writer, T x)
		{
			writer.Int(static_cast<int>(x));
		}
		static TrivialValue<T> TempRead(const rapidjson::Value* x)
		{
			return TrivialValue<T>(static_cast<T>(x ? x->GetInt() : 0));
		}
		static TrivialValue<T> PempRead(const rapidjson::Value* x)
		{
			return TrivialValue<T>(static_cast<T>(x ? x->GetInt() : 0));
		}
	};
}