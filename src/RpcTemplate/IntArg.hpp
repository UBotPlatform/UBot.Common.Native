#pragma once
#include "TrivialValue.hpp"
#include "JsonRpc.h"
namespace ubot
{
	struct IntArg
	{
		using NativeType = int;
		static void Write(TWriter& writer, int x)
		{
			writer.Int(x);
		}
		static TrivialValue<int> TempRead(const rapidjson::Value* x)
		{
			return TrivialValue<int>(x ? x->GetInt() : 0);
		}
		static TrivialValue<int> PempRead(const rapidjson::Value* x)
		{
			return TrivialValue<int>(x ? x->GetInt() : 0);
		}
	};
}