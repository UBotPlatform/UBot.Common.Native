#include <skyr/percent_encoding/percent_encode.hpp>
#include "UBotClientHost.h"
#include "AppHost.h"
#include "UNativeStrHelper.h"
#include "RpcTemplate/RpcTemplateImpl.hpp"
#include "UBotAppContext.h"
using namespace ubot;

Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetGroupName)(void* ctx, Encoding::ConstStr bot, Encoding::ConstStr id)
{
    auto context = static_cast<AppContext*>(ctx);
    thread_local static auto data = CallFromNative<StringArg, StringArg, StringArg>(context->rpc, "get_group_name", bot, id);
    return data.get();
}
void __stdcall UNativeStr_WithSuffix(ubotAppGetGroupNameAsync)(void* ctx, void* user, Encoding::ConstStr bot, Encoding::ConstStr id,
    void(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr result))
{
    auto context = static_cast<AppContext*>(ctx);
    CallFromNativeAsync<StringArg, StringArg, StringArg>(context->rpc, "get_group_name", bot, id, std::bind_front(handler, ctx, user));
}

Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetUserName)(void* ctx, Encoding::ConstStr bot, Encoding::ConstStr id)
{
    auto context = static_cast<AppContext*>(ctx);
    thread_local static auto data = CallFromNative<StringArg, StringArg, StringArg>(context->rpc, "get_user_name", bot, id);
    return data.get();
}
void __stdcall UNativeStr_WithSuffix(ubotAppGetUserNameAsync)(void* ctx, void* user, Encoding::ConstStr bot, Encoding::ConstStr id,
    void(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr result))
{
    auto context = static_cast<AppContext*>(ctx);
    CallFromNativeAsync<StringArg, StringArg, StringArg>(context->rpc, "get_user_name", bot, id, std::bind_front(handler, ctx, user));
}

void __stdcall UNativeStr_WithSuffix(ubotAppSendChatMessage)(void* ctx, Encoding::ConstStr bot, ChatMessageType type, Encoding::ConstStr source, Encoding::ConstStr target, Encoding::ConstStr message)
{
    auto context = static_cast<AppContext*>(ctx);
    CallFromNative<void, StringArg, EnumArg<ChatMessageType>, StringArg, StringArg, StringArg>(context->rpc, "send_chat_message", bot, type, source, target, message);
}
void __stdcall UNativeStr_WithSuffix(ubotAppSendChatMessageAsync)(void* ctx, void* user, Encoding::ConstStr bot, ChatMessageType type, Encoding::ConstStr source, Encoding::ConstStr target, Encoding::ConstStr message,
    void(__stdcall* handler)(void* ctx, void* user))
{
    auto context = static_cast<AppContext*>(ctx);
    CallFromNativeAsync<void, StringArg, EnumArg<ChatMessageType>, StringArg, StringArg, StringArg>(context->rpc, "send_chat_message", bot, type, source, target, message, std::bind_front(handler, ctx, user));
}

void __stdcall UNativeStr_WithSuffix(ubotAppRemoveMember)(void* ctx, Encoding::ConstStr bot, Encoding::ConstStr source, Encoding::ConstStr target)
{
    auto context = static_cast<AppContext*>(ctx);
    CallFromNative<void, StringArg, StringArg, StringArg>(context->rpc, "remove_member", bot, source, target);
}
void __stdcall UNativeStr_WithSuffix(ubotAppRemoveMemberAsync)(void* ctx, void* user, Encoding::ConstStr bot, Encoding::ConstStr source, Encoding::ConstStr target,
    void(__stdcall* handler)(void* ctx, void* user))
{
    auto context = static_cast<AppContext*>(ctx);
    CallFromNativeAsync<void, StringArg, StringArg, StringArg>(context->rpc, "remove_member", bot, source, target, std::bind_front(handler, ctx, user));
}

void __stdcall UNativeStr_WithSuffix(ubotAppShutupMember)(void* ctx, Encoding::ConstStr bot, Encoding::ConstStr source, Encoding::ConstStr target, int duration)
{
    auto context = static_cast<AppContext*>(ctx);
    CallFromNative<void, StringArg, StringArg, StringArg, IntArg>(context->rpc, "shutup_member", bot, source, target, duration);
}
void __stdcall UNativeStr_WithSuffix(ubotAppShutupMemberAsync)(void* ctx, void* user, Encoding::ConstStr bot, Encoding::ConstStr source, Encoding::ConstStr target, int duration,
    void(__stdcall* handler)(void* ctx, void* user))
{
    auto context = static_cast<AppContext*>(ctx);
    CallFromNativeAsync<void, StringArg, StringArg, StringArg, IntArg>(context->rpc, "shutup_member", bot, source, target, duration, std::bind_front(handler, ctx, user));
}

void __stdcall UNativeStr_WithSuffix(ubotAppShutupAllMember)(void* ctx, Encoding::ConstStr bot, Encoding::ConstStr source, bool shutupSwitch)
{
    auto context = static_cast<AppContext*>(ctx);
    CallFromNative<void, StringArg, StringArg, BoolArg>(context->rpc, "shutup_all_member", bot, source, shutupSwitch);
}
void __stdcall UNativeStr_WithSuffix(ubotAppShutupAllMemberAsync)(void* ctx, void* user, Encoding::ConstStr bot, Encoding::ConstStr source, bool shutupSwitch,
    void(__stdcall* handler)(void* ctx, void* user))
{
    auto context = static_cast<AppContext*>(ctx);
    CallFromNativeAsync<void, StringArg, StringArg, BoolArg>(context->rpc, "shutup_all_member", bot, source, shutupSwitch, std::bind_front(handler, ctx, user));
}

Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetMemberName)(void* ctx, Encoding::ConstStr bot, Encoding::ConstStr source, Encoding::ConstStr target)
{
    auto context = static_cast<AppContext*>(ctx);
    thread_local static auto data = CallFromNative<StringArg, StringArg, StringArg, StringArg>(context->rpc, "get_member_name", bot, source, target);
    return data.get();
}
void __stdcall UNativeStr_WithSuffix(ubotAppGetMemberNameAsync)(void* ctx, void* user, Encoding::ConstStr bot, Encoding::ConstStr source, Encoding::ConstStr target,
    void(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr result))
{
    auto context = static_cast<AppContext*>(ctx);
    CallFromNativeAsync<StringArg, StringArg, StringArg, StringArg>(context->rpc, "get_member_name", bot, source, target, std::bind_front(handler, ctx, user));
}

Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetUserAvatar)(void* ctx, Encoding::ConstStr bot, Encoding::ConstStr id)
{
    auto context = static_cast<AppContext*>(ctx);
    thread_local static auto data = CallFromNative<StringArg, StringArg, StringArg>(context->rpc, "get_user_avatar", bot, id);
    return data.get();
}
void __stdcall UNativeStr_WithSuffix(ubotAppGetUserAvatarAsync)(void* ctx, void* user, Encoding::ConstStr bot, Encoding::ConstStr id,
    void(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr result))
{
    auto context = static_cast<AppContext*>(ctx);
    CallFromNativeAsync<StringArg, StringArg, StringArg>(context->rpc, "get_user_avatar", bot, id, std::bind_front(handler, ctx, user));
}

Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetSelfID)(void* ctx, Encoding::ConstStr bot)
{
    auto context = static_cast<AppContext*>(ctx);
    thread_local static auto data = CallFromNative<StringArg, StringArg>(context->rpc, "get_self_id", bot);
    return data.get();
}
void __stdcall UNativeStr_WithSuffix(ubotAppGetSelfIDAsync)(void* ctx, void* user, Encoding::ConstStr bot,
    void(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr result))
{
    auto context = static_cast<AppContext*>(ctx);
    CallFromNativeAsync<StringArg, StringArg>(context->rpc, "get_self_id", bot, std::bind_front(handler, ctx, user));
}

Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetPlatformID)(void* ctx, Encoding::ConstStr bot)
{
    auto context = static_cast<AppContext*>(ctx);
    thread_local static auto data = CallFromNative<StringArg, StringArg>(context->rpc, "get_platform_id", bot);
    return data.get();
}
void __stdcall UNativeStr_WithSuffix(ubotAppGetPlatformIDAsync)(void* ctx, void* user, Encoding::ConstStr bot,
    void(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr result))
{
    auto context = static_cast<AppContext*>(ctx);
    CallFromNativeAsync<StringArg, StringArg>(context->rpc, "get_platform_id", bot, std::bind_front(handler, ctx, user));
}

Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetGroupList)(void* ctx, Encoding::ConstStr bot)
{
    auto context = static_cast<AppContext*>(ctx);
    thread_local static auto data = CallFromNative<FlattedStringArrayArg<>, StringArg>(context->rpc, "get_group_list", bot);
    return data.get();
}
void __stdcall UNativeStr_WithSuffix(ubotAppGetGroupListAsync)(void* ctx, void* user, Encoding::ConstStr bot,
    void(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr result))
{
    auto context = static_cast<AppContext*>(ctx);
    CallFromNativeAsync<FlattedStringArrayArg<>, StringArg>(context->rpc, "get_group_list", bot, std::bind_front(handler, ctx, user));
}

Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetMemberList)(void* ctx, Encoding::ConstStr bot, Encoding::ConstStr id)
{
    auto context = static_cast<AppContext*>(ctx);
    thread_local static auto data = CallFromNative<FlattedStringArrayArg<>, StringArg, StringArg>(context->rpc, "get_member_list", bot, id);
    return data.get();
}
void __stdcall UNativeStr_WithSuffix(ubotAppGetMemberListAsync)(void* ctx, void* user, Encoding::ConstStr bot, Encoding::ConstStr id,
    void(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr result))
{
    auto context = static_cast<AppContext*>(ctx);
    CallFromNativeAsync<FlattedStringArrayArg<>, StringArg, StringArg>(context->rpc, "get_member_list", bot, id, std::bind_front(handler, ctx, user));
}

void __stdcall UNativeStr_WithSuffix(ubotAppSetOnReceiveChatMessageHandler)(void* ctx, void* user,
    EventResultType(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr bot, ChatMessageType type, Encoding::ConstStr source, Encoding::ConstStr sender, Encoding::ConstStr message, Encoding::ConstStr info))
{
    auto context = static_cast<AppContext*>(ctx);
    // bot, type, source, sender, message, info
    SetNativeHandler<NormalEventRespond, StringArg, EnumArg<ChatMessageType>, StringArg, StringArg, StringArg, JsonRawArg>(context->rpc, "on_receive_chat_message", std::bind_front(handler, ctx, user));
}

void __stdcall UNativeStr_WithSuffix(ubotAppSetOnReceiveChatMessageAsyncHandler)(void* ctx, void* user,
    EventResultType(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr bot, ChatMessageType type, Encoding::ConstStr source, Encoding::ConstStr sender, Encoding::ConstStr message, Encoding::ConstStr info, void* async))
{
    auto context = static_cast<AppContext*>(ctx);
    // bot, type, source, sender, message, info
    SetNativeAsyncHandler<StringArg, EnumArg<ChatMessageType>, StringArg, StringArg, StringArg, JsonRawArg>(context->rpc, "on_receive_chat_message", std::bind_front(handler, ctx, user));
}

void __stdcall UNativeStr_WithSuffix(ubotAppSetOnMemberJoinedHandler)(void* ctx, void* user,
    EventResultType(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr bot, Encoding::ConstStr source, Encoding::ConstStr sender, Encoding::ConstStr inviter))
{
    auto context = static_cast<AppContext*>(ctx);
    // bot, source, sender, inviter
    SetNativeHandler<NormalEventRespond, StringArg, StringArg, StringArg, StringArg>(context->rpc, "on_member_joined", std::bind_front(handler, ctx, user));
}

void __stdcall UNativeStr_WithSuffix(ubotAppSetOnMemberJoinedAsyncHandler)(void* ctx, void* user,
    EventResultType(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr bot, Encoding::ConstStr source, Encoding::ConstStr sender, Encoding::ConstStr inviter, void* async))
{
    auto context = static_cast<AppContext*>(ctx);
    // bot, source, sender, inviter
    SetNativeAsyncHandler<StringArg, StringArg, StringArg, StringArg>(context->rpc, "on_member_joined", std::bind_front(handler, ctx, user));
}

void __stdcall UNativeStr_WithSuffix(ubotAppSetOnMemberLeftHandler)(void* ctx, void* user,
    EventResultType(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr bot, Encoding::ConstStr source, Encoding::ConstStr sender))
{
    auto context = static_cast<AppContext*>(ctx);
    // bot, source, sender
    SetNativeHandler<NormalEventRespond, StringArg, StringArg, StringArg>(context->rpc, "on_member_left", std::bind_front(handler, ctx, user));
}

void __stdcall UNativeStr_WithSuffix(ubotAppSetOnMemberLeftAsyncHandler)(void* ctx, void* user,
    EventResultType(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr bot, Encoding::ConstStr source, Encoding::ConstStr sender, void* async))
{
    auto context = static_cast<AppContext*>(ctx);
    // bot, source, sender
    SetNativeAsyncHandler<StringArg, StringArg, StringArg>(context->rpc, "on_member_left", std::bind_front(handler, ctx, user));
}

void __stdcall UNativeStr_WithSuffix(ubotAppSetProcessGroupInvitationHandler)(void* ctx, void* user,
    EventResultType(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr bot, Encoding::ConstStr sender, Encoding::ConstStr target, Encoding::ConstStr reason, void* respondedReason))
{
    auto context = static_cast<AppContext*>(ctx);
    // bot, source, target, reason
    SetNativeHandler<ReasonableEventRespond, StringArg, StringArg, StringArg, StringArg>(context->rpc, "process_group_invitation", std::bind_front(handler, ctx, user));
}

void __stdcall UNativeStr_WithSuffix(ubotAppSetProcessGroupInvitationAsyncHandler)(void* ctx, void* user,
    EventResultType(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr bot, Encoding::ConstStr sender, Encoding::ConstStr target, Encoding::ConstStr reason, void* async))
{
    auto context = static_cast<AppContext*>(ctx);
    // bot, source, target, reason
    SetNativeAsyncHandler<StringArg, StringArg, StringArg, StringArg>(context->rpc, "process_group_invitation", std::bind_front(handler, ctx, user));
}

void __stdcall UNativeStr_WithSuffix(ubotAppSetProcessFriendRequestHandler)(void* ctx, void* user,
    EventResultType(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr bot, Encoding::ConstStr sender, Encoding::ConstStr reason, void* respondedReason))
{
    auto context = static_cast<AppContext*>(ctx);
    // bot, sender, reason
    SetNativeHandler<ReasonableEventRespond, StringArg, StringArg, StringArg>(context->rpc, "process_friend_request", std::bind_front(handler, ctx, user));
}

void __stdcall UNativeStr_WithSuffix(ubotAppSetProcessFriendRequestAsyncHandler)(void* ctx, void* user,
    EventResultType(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr bot, Encoding::ConstStr sender, Encoding::ConstStr reason, void* async))
{
    auto context = static_cast<AppContext*>(ctx);
    // bot, sender, reason
    SetNativeAsyncHandler<StringArg, StringArg, StringArg>(context->rpc, "process_friend_request", std::bind_front(handler, ctx, user));
}

void __stdcall UNativeStr_WithSuffix(ubotAppSetProcessMembershipRequestHandler)(void* ctx, void* user,
    EventResultType(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr bot, Encoding::ConstStr source, Encoding::ConstStr sender, Encoding::ConstStr inviter, Encoding::ConstStr reason, void* respondedReason))
{
    auto context = static_cast<AppContext*>(ctx);
    // bot, source, sender, inviter, reason
    SetNativeHandler<ReasonableEventRespond, StringArg, StringArg, StringArg, StringArg, StringArg>(context->rpc, "process_membership_request", std::bind_front(handler, ctx, user));
}

void __stdcall UNativeStr_WithSuffix(ubotAppSetProcessMembershipRequestAsyncHandler)(void* ctx, void* user,
    EventResultType(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr bot, Encoding::ConstStr source, Encoding::ConstStr sender, Encoding::ConstStr inviter, Encoding::ConstStr reason, void* async))
{
    auto context = static_cast<AppContext*>(ctx);
    // bot, source, sender, inviter, reason
    SetNativeAsyncHandler<StringArg, StringArg, StringArg, StringArg, StringArg>(context->rpc, "process_membership_request", std::bind_front(handler, ctx, user));
}

void __stdcall UNativeStr_WithSuffix(ubotAppHost)(
    void* ctx,
    Encoding::ConstStr op,
    Encoding::ConstStr urlStr,
    Encoding::ConstStr id)
{
    auto context = static_cast<AppContext*>(ctx);
    HostUBotClient(EncodingImpl::TempFrom(op).get(), 
        EncodingImpl::TempFrom(urlStr).get(), 
        &context->rpc,
        [=](const skyr::url& managerUrl, JsonRpc& rpc) -> std::string {
            auto clientUrl = managerUrl;
            std::string clientTken;
            auto registered = cppcoro::sync_wait(rpc.Call("register_app", [&](TWriter& writer)
                {
                    writer.StartArray();
                    writer.String(EncodingImpl::TempFrom(id).get());
                    writer.EndArray();
                }, true));
            if (registered.Error.has_value())
            {
                return "";
            }
            clientUrl.set_pathname("/api/app");
            clientUrl.set_search("?id=" + skyr::percent_encode(std::string(EncodingImpl::TempFrom(id).get())) + "&token=" + registered.Result.GetString());
            return clientUrl.href();
        }, context->startup);
}