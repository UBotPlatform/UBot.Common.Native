#pragma once
#include "TrivialValue.hpp"
#include "JsonRpc.h"
namespace ubot
{
	struct BoolArg
	{
		using NativeType = int;
		static void Write(TWriter& writer, bool x)
		{
			writer.Bool(x);
		}
		static TrivialValue<bool> TempRead(const rapidjson::Value* x)
		{
			return TrivialValue<bool>(x ? x->GetBool() : false);
		}
		static TrivialValue<bool> PempRead(const rapidjson::Value* x)
		{
			return TrivialValue<bool>(x ? x->GetBool() : false);
		}
	};
}