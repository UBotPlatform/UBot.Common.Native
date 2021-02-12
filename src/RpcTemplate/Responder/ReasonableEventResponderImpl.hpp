#pragma once
#include <RpcTemplate/Responder/ReasonableEventResponder.hpp>
#include "ResponderImpl.hpp"
#include "../../JsonRpc.h"
#include "EventResultType.h"
namespace ubot
{
    template<>
    struct ResponderImpl<ReasonableEventResponder>
    {
        static void Respond(TWriter& writer, EventResultType x, void* reason)
        {
            JsonRpc::StartResult(writer);
            writer.StartObject();
            writer.Key("type");
            writer.Int(static_cast<int>(x));
            writer.Key("reason");
            writer.String(static_cast<std::string*>(reason)->c_str());
            writer.EndObject();
            JsonRpc::EndResult(writer);
        }
        static auto MakeResultEx()
        {
            return std::make_unique<std::string>();
        }
    };
}