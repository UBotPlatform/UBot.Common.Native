#include "UBotAppContext.h"

void* __stdcall ubotAppNew()
{
    auto context = new ubot::AppContext();
    const char* handler_names[] = {
        "on_receive_chat_message",
        "on_member_joined",
        "on_member_left",
        "process_group_invitation",
        "process_friend_request",
        "process_membership_request"
    };
    for (auto name : handler_names)
    {
        context->rpc.SetHandler(name, [](rapidjson::Value&& params, ubot::TWriter& writer)
            {
                ubot::JsonRpc::StartResult(writer);
                writer.StartObject();
                writer.Key("type");
                writer.Int(0);
                writer.EndObject();
                ubot::JsonRpc::EndResult(writer);
            });
    }
    context->startup = [] {};
    return context;
}

void __stdcall ubotAppDelete(void* ctx)
{
    delete static_cast<ubot::AppContext*>(ctx);
}