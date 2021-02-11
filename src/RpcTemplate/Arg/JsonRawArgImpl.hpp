#pragma once
#include <RpcTemplate/Arg/JsonRawArg.hpp>
#include "ArgImpl.hpp"
#include "../TrivialValue.hpp"
#include "../../JsonRpc.h"
#include "../../UNativeStrHelper.h"
namespace ubot
{
	template<>
	struct ArgImpl<JsonRawArg>
	{
		static void Write(TWriter& writer, Encoding::ConstStr x)
		{
			EncodingImpl::TempFrom utf8(x);
			rapidjson::Reader reader;
			rapidjson::StringStream ss(utf8.get());
			reader.Parse(ss, writer);
		}
		static auto TempRead(const rapidjson::Value* x)
		{
			return PempRead(x);
		}
		static EncodingImpl::PermTo PempRead(const rapidjson::Value* x)
		{
			if (x == nullptr)
			{
				return EncodingImpl::PermTo(nullptr);
			}
			rapidjson::StringBuffer text;
			TWriter writer(text);
			x->Accept(writer);
			writer.Flush();
			return EncodingImpl::PermTo(text.GetString());
		}
	};
}