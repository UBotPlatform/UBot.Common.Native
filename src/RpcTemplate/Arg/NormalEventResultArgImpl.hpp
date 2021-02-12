#pragma once
#include <RpcTemplate/Arg/NormalEventResultArg.hpp>
#include "ArgImpl.hpp"
#include "../TrivialValue.hpp"
#include "../../JsonRpc.h"
#include "../../UNativeStrHelper.h"
namespace ubot
{
	template<>
	struct ArgImpl<NormalEventResultArg>
	{
		static void Write(TWriter& writer, EventResultType x)
		{
			writer.StartObject();
			writer.Key("type");
			writer.Int(static_cast<int>(x));
			writer.EndObject();
		}
		static auto TempRead(const rapidjson::Value* x)
		{
			return PempRead(x);
		}
		static TrivialValue<EventResultType> PempRead(const rapidjson::Value* x)
		{
			if (x != nullptr && x->IsObject())
			{
				auto pType = x->FindMember("type");
				if (pType != x->MemberEnd())
				{
					return static_cast<EventResultType>(pType->value.GetInt());
				}
			}
			return EventResultType::Ignore;
		}
	};
}