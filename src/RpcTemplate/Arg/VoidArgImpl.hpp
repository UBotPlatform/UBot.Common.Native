#pragma once
#include <RpcTemplate/Arg/VoidArg.hpp>
#include "ArgImpl.hpp"
#include "../TrivialValue.hpp"
#include "../../JsonRpc.h"
namespace ubot
{
	template<>
	struct ArgImpl<VoidArg>
	{
		static void Write(TWriter& writer, ...)
		{
			writer.Null();
		}
		static TrivialValue<void> TempRead(const rapidjson::Value* x)
		{
			return {};
		}
		static TrivialValue<void> PempRead(const rapidjson::Value* x)
		{
			return {};
		}
	};
}