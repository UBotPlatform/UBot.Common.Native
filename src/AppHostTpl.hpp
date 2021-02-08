#include <skyr/percent_encoding/percent_encode.hpp>
#include "UBotClientHost.h"
#include "AppHost.h"
#include "UNativeStrHelper.h"
#include "RpcTemplate.hpp"
#include "UBotAppContext.h"
using namespace ubot;
struct NormalEventRespond
{
    using NativeType = EventResultType;
    using NativeTypeEx = void;
    static void Respond(TWriter& writer, EventResultType x)
    {
        JsonRpc::StartResult(writer);
        writer.StartObject();
        writer.Key("type");
        writer.Int(static_cast<int>(x));
        writer.EndObject();
        JsonRpc::EndResult(writer);
    }
}; 

struct ReasonableEventRespond
{
    using NativeType = EventResultType;
    using NativeTypeEx = void*;
    static void Respond(TWriter& writer, EventResultType x, void* reason)
    {
        JsonRpc::StartResult(writer);
        writer.StartObject();
        writer.Key("type");
        writer.Int(static_cast<int>(x));
        writer.Key("reason");
        writer.String(static_cast<std::string *>(reason)->c_str());
        writer.EndObject();
        JsonRpc::EndResult(writer);
    }
    static auto MakeResultEx()
    {
        return std::make_unique<std::string>();
    }
};

Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetGroupName)(void* ctx, Encoding::ConstStr bot, Encoding::ConstStr id)
{
    auto context = static_cast<AppContext*>(ctx);
    thread_local static auto data = CallFromNative<StringArg, StringArg, StringArg>(context->rpc, "get_group_name", bot, id);
    return data.get();
}

Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetUserName)(void* ctx, Encoding::ConstStr bot, Encoding::ConstStr id)
{
    auto context = static_cast<AppContext*>(ctx);
    thread_local static auto data = CallFromNative<StringArg, StringArg, StringArg>(context->rpc, "get_user_name", bot, id);
    return data.get();
}

void __stdcall UNativeStr_WithSuffix(ubotAppSendChatMessage)(void* ctx, Encoding::ConstStr bot, ChatMessageType type, Encoding::ConstStr source, Encoding::ConstStr target, Encoding::ConstStr message)
{
    auto context = static_cast<AppContext*>(ctx);
    CallFromNative<void, StringArg, EnumArg<ChatMessageType>, StringArg, StringArg, StringArg>(context->rpc, "send_chat_message", bot, type, source, target, message);
}

void __stdcall UNativeStr_WithSuffix(ubotAppRemoveMember)(void* ctx, Encoding::ConstStr bot, Encoding::ConstStr source, Encoding::ConstStr target)
{
    auto context = static_cast<AppContext*>(ctx);
    CallFromNative<void, StringArg, StringArg, StringArg>(context->rpc, "remove_member", bot, source, target);
}

void __stdcall UNativeStr_WithSuffix(ubotAppShutupMember)(void* ctx, Encoding::ConstStr bot, Encoding::ConstStr source, Encoding::ConstStr target, int duration)
{
    auto context = static_cast<AppContext*>(ctx);
    CallFromNative<void, StringArg, StringArg, StringArg, IntArg>(context->rpc, "remove_member", bot, source, target, duration);
}

void __stdcall UNativeStr_WithSuffix(ubotAppShutupAllMember)(void* ctx, Encoding::ConstStr bot, Encoding::ConstStr source, bool shutupSwitch)
{
    auto context = static_cast<AppContext*>(ctx);
    CallFromNative<void, StringArg, StringArg, BoolArg>(context->rpc, "shutup_all_member", bot, source, shutupSwitch);
}

Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetMemberName)(void* ctx, Encoding::ConstStr bot, Encoding::ConstStr source, Encoding::ConstStr target)
{
    auto context = static_cast<AppContext*>(ctx);
    thread_local static auto data = CallFromNative<StringArg, StringArg, StringArg, StringArg>(context->rpc, "get_member_name", bot, source, target);
    return data.get();
}

Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetUserAvatar)(void* ctx, Encoding::ConstStr bot, Encoding::ConstStr id)
{
    auto context = static_cast<AppContext*>(ctx);
    thread_local static auto data = CallFromNative<StringArg, StringArg, StringArg>(context->rpc, "get_user_avatar", bot, id);
    return data.get();
}

Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetSelfID)(void* ctx, Encoding::ConstStr bot)
{
    auto context = static_cast<AppContext*>(ctx);
    thread_local static auto data = CallFromNative<StringArg, StringArg>(context->rpc, "get_self_id", bot);
    return data.get();
}

Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetPlatformID)(void* ctx, Encoding::ConstStr bot)
{
    auto context = static_cast<AppContext*>(ctx);
    thread_local static auto data = CallFromNative<StringArg, StringArg>(context->rpc, "get_platform_id", bot);
    return data.get();
}

Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetGroupList)(void* ctx, Encoding::ConstStr bot)
{
    auto context = static_cast<AppContext*>(ctx);
    thread_local static auto data = CallFromNative<FlattedStringArrayArg<>, StringArg>(context->rpc, "get_group_list", bot);
    return data.get();
}

Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetMemberList)(void* ctx, Encoding::ConstStr bot, Encoding::ConstStr id)
{
    auto context = static_cast<AppContext*>(ctx);
    thread_local static auto data = CallFromNative<FlattedStringArrayArg<>, StringArg, StringArg>(context->rpc, "get_member_list", bot, id);
    return data.get();
}

void __stdcall UNativeStr_WithSuffix(ubotAppSetOnReceiveChatMessageHandler)(void* ctx, void* user,
    EventResultType(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr bot, ChatMessageType type, Encoding::ConstStr source, Encoding::ConstStr sender, Encoding::ConstStr message, Encoding::ConstStr info))
{
    auto context = static_cast<AppContext*>(ctx);
    // bot, type, source, sender, message, info
    SetNativeHandler<NormalEventRespond, StringArg, EnumArg<ChatMessageType>, StringArg, StringArg, StringArg, JsonRawArg>(context->rpc, "on_receive_chat_message", std::bind_front(handler, ctx, user));
}

void __stdcall UNativeStr_WithSuffix(ubotAppSetOnMemberJoinedHandler)(void* ctx, void* user,
    EventResultType(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr bot, Encoding::ConstStr source, Encoding::ConstStr sender, Encoding::ConstStr inviter))
{
    auto context = static_cast<AppContext*>(ctx);
    // bot, source, sender, inviter
    SetNativeHandler<NormalEventRespond, StringArg, StringArg, StringArg, StringArg>(context->rpc, "on_member_joined", std::bind_front(handler, ctx, user));
}

void __stdcall UNativeStr_WithSuffix(ubotAppSetOnMemberLeftHandler)(void* ctx, void* user,
    EventResultType(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr bot, Encoding::ConstStr source, Encoding::ConstStr sender))
{
    auto context = static_cast<AppContext*>(ctx);
    // bot, source, sender
    SetNativeHandler<NormalEventRespond, StringArg, StringArg, StringArg>(context->rpc, "on_member_left", std::bind_front(handler, ctx, user));
}

void __stdcall UNativeStr_WithSuffix(ubotAppSetProcessGroupInvitationHandler)(void* ctx, void* user,
    EventResultType(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr bot, Encoding::ConstStr sender, Encoding::ConstStr target, Encoding::ConstStr reason, void* respondedReason))
{
    auto context = static_cast<AppContext*>(ctx);
    // bot, source, target, reason
    SetNativeHandler<ReasonableEventRespond, StringArg, StringArg, StringArg, StringArg>(context->rpc, "process_group_invitation", std::bind_front(handler, ctx, user));
}

void __stdcall UNativeStr_WithSuffix(ubotAppSetProcessFriendRequestHandler)(void* ctx, void* user,
    EventResultType(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr bot, Encoding::ConstStr sender, Encoding::ConstStr reason, void* respondedReason))
{
    auto context = static_cast<AppContext*>(ctx);
    // bot, sender, reason
    SetNativeHandler<ReasonableEventRespond, StringArg, StringArg, StringArg>(context->rpc, "process_friend_request", std::bind_front(handler, ctx, user));
}

void __stdcall UNativeStr_WithSuffix(ubotAppSetProcessMembershipRequestHandler)(void* ctx, void* user,
    EventResultType(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr bot, Encoding::ConstStr source, Encoding::ConstStr sender, Encoding::ConstStr inviter, Encoding::ConstStr reason, void* respondedReason))
{
    auto context = static_cast<AppContext*>(ctx);
    // bot, source, sender, inviter, reason
    SetNativeHandler<ReasonableEventRespond, StringArg, StringArg, StringArg, StringArg, StringArg>(context->rpc, "process_membership_request", std::bind_front(handler, ctx, user));
}


void __stdcall UNativeStr_WithSuffix(ubotAppHost)(
    void* ctx,
    Encoding::ConstStr op,
    Encoding::ConstStr urlStr,
    Encoding::ConstStr id,
    bool mtf)
{
    auto context = static_cast<AppContext*>(ctx);
    HostUBotClient(EncodingImpl::TempFrom(op).get(), 
        EncodingImpl::TempFrom(urlStr).get(), 
        &context->rpc,
        mtf,
        [=](const skyr::url& managerUrl, JsonRpc& rpc) -> std::string {
            auto clientUrl = managerUrl;
            std::string clientTken;
            auto registered = rpc.Call("register_app", [&](TWriter& writer)
                {
                    writer.StartArray();
                    writer.String(EncodingImpl::TempFrom(id).get());
                    writer.EndArray();
                });
            if (registered.Error.has_value())
            {
                return "";
            }
            clientUrl.set_pathname("/api/app");
            clientUrl.set_search("?id=" + skyr::percent_encode(std::string(EncodingImpl::TempFrom(id).get())) + "&token=" + registered.Result.GetString());
            return clientUrl.href();
        }, context->startup);
}