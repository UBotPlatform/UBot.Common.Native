#pragma once
#include <RpcTemplate/Arg/IntArg.hpp>
#include "ArgImpl.hpp"
#include "../TrivialValue.hpp"
#include "../../JsonRpc.h"
namespace ubot
{
	template<>
	struct ArgImpl<IntArg>
	{
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