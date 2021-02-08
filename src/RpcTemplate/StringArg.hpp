#pragma once
#include "JsonRpc.h"
#include "UNativeStrHelper.h"
namespace ubot
{
	struct StringArg
	{
		using NativeType = EncodingImpl::ConstStr;
		static void Write(TWriter& writer, EncodingImpl::ConstStr x)
		{
			writer.String(EncodingImpl::TempFrom(x).get());
		}
		static EncodingImpl::TempTo TempRead(const rapidjson::Value* x)
		{
			return EncodingImpl::TempTo(x ? x->GetString() : nullptr);
		}
		static EncodingImpl::PermTo PempRead(const rapidjson::Value* x)
		{
			return EncodingImpl::PermTo(x ? x->GetString() : nullptr);
		}
	};
}