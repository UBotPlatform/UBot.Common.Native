#pragma once
#include <RpcTemplate/Arg/BoolArg.hpp>
#include "ArgImpl.hpp"
#include "../TrivialValue.hpp"
#include "../../JsonRpc.h"
namespace ubot
{
	template<>
	struct ArgImpl<BoolArg>
	{
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