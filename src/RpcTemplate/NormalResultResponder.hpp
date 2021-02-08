#pragma once
#include "JsonRpc.h"
namespace ubot
{
	template<typename TArg>
	struct NormalResultResponder
	{
		using NativeType = typename TArg::NativeType;
		using NativeTypeEx = void;
		static void Respond(TWriter& writer, typename TArg::NativeType x)
		{
			JsonRpc::StartResult(writer);
			TArg::Write(writer, x);
			JsonRpc::EndResult(writer);
		}
	};
}