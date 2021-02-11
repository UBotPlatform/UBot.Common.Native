#pragma once
#include <RpcTemplate/Responder/NormalResultResponder.hpp>
#include "ResponderImpl.hpp"
#include "../../JsonRpc.h"
namespace ubot
{
	template<typename TArg>
	struct ResponderImpl<NormalResultResponder<TArg>>
	{
		static void Respond(TWriter& writer, typename TArg::NativeType x)
		{
			JsonRpc::StartResult(writer);
			TArg::Write(writer, x);
			JsonRpc::EndResult(writer);
		}
	};
}