#include <skyr/percent_encoding/percent_encode.hpp>
#include "UBotClientHost.h"
#include "AppHost.h"
#include "UNativeStrHelper.h"
#include "UBotAppContext.h"
using namespace ubot;

inline void WriteEventResult(TWriter& writer, EventResultType type)
{
    JsonRpc::StartResult(writer);
    writer.StartObject();
    writer.Key("type");
    writer.Int(static_cast<int>(type));
    writer.EndObject();
    JsonRpc::EndResult(writer);
}

inline void WriteEventResultWithReason(TWriter& writer, EventResultType type, Encoding::ConstStr reason)
{
    JsonRpc::StartResult(writer);
    writer.StartObject();
    writer.Key("type");
    writer.Int(static_cast<int>(type));
    writer.Key("reason");
    writer.String(EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(reason)));
    writer.EndObject();
    JsonRpc::EndResult(writer);
}

inline std::string fromStringArray(const rapidjson::Value& a, const char* separator) {
    std::string r;
    if (!a.IsArray()) {
        return r;
    }
    auto iter = a.Begin();
    auto end = a.End();
    if (iter != end) {
        if (!iter->IsString())
        {
            r.append("<error>");
        }
        else
        {
            r.append(iter->GetString(), iter->GetStringLength());
        }
        iter++;
    }
    for (; iter != end; ++iter)
    {
        r.append(separator);
        if (!iter->IsString())
        {
            r.append("<error>");
        }
        else
        {
            r.append(iter->GetString(), iter->GetStringLength());
        }
    }
    return r;
}

Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetGroupName)(void* ctx, Encoding::ConstStr bot, Encoding::ConstStr id)
{
    auto context = static_cast<AppContext*>(ctx);
    auto rpcResult = context->rpc.Call("get_group_name", [&](TWriter& writer)
        {
            writer.StartArray();
            writer.String(EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(bot)));
            writer.String(EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(id)));
            writer.EndArray();
        });
    auto result = rpcResult.Result.IsString() ? rpcResult.Result.GetString() : nullptr;
    static auto data = EncodingImpl::PermTo_S(result);
    return EncodingImpl::PermTo_G(data);
}

Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetUserName)(void* ctx, Encoding::ConstStr bot, Encoding::ConstStr id)
{
    auto context = static_cast<AppContext*>(ctx);
    auto rpcResult = context->rpc.Call("get_user_name", [&](TWriter& writer)
        {
            writer.StartArray();
            writer.String(EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(bot)));
            writer.String(EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(id)));
            writer.EndArray();
        });
    auto result = rpcResult.Result.IsString() ? rpcResult.Result.GetString() : nullptr;
    static auto data = EncodingImpl::PermTo_S(result);
    return EncodingImpl::PermTo_G(data);
}

void __stdcall UNativeStr_WithSuffix(ubotAppSendChatMessage)(void* ctx, Encoding::ConstStr bot, ChatMessageType type, Encoding::ConstStr source, Encoding::ConstStr target, Encoding::ConstStr message)
{
    auto context = static_cast<AppContext*>(ctx);
    auto rpcResult = context->rpc.Call("send_chat_message", [&](TWriter& writer)
        {
            writer.StartArray();
            writer.String(EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(bot)));
            writer.Int(static_cast<int>(type));
            writer.String(EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(source)));
            writer.String(EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(target)));
            writer.String(EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(message)));
            writer.EndArray();
        });
}

void __stdcall UNativeStr_WithSuffix(ubotAppRemoveMember)(void* ctx, Encoding::ConstStr bot, Encoding::ConstStr source, Encoding::ConstStr target)
{
    auto context = static_cast<AppContext*>(ctx);
    auto rpcResult = context->rpc.Call("remove_member", [&](TWriter& writer)
        {
            writer.StartArray();
            writer.String(EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(bot)));
            writer.String(EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(source)));
            writer.String(EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(target)));
            writer.EndArray();
        });
}

void __stdcall UNativeStr_WithSuffix(ubotAppShutupMember)(void* ctx, Encoding::ConstStr bot, Encoding::ConstStr source, Encoding::ConstStr target, int duration)
{
    auto context = static_cast<AppContext*>(ctx);
    auto rpcResult = context->rpc.Call("shutup_member", [&](TWriter& writer)
        {
            writer.StartArray();
            writer.String(EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(bot)));
            writer.String(EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(source)));
            writer.String(EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(target)));
            writer.Int(duration);
            writer.EndArray();
        });
}

void __stdcall UNativeStr_WithSuffix(ubotAppShutupAllMember)(void* ctx, Encoding::ConstStr bot, Encoding::ConstStr source, bool shutupSwitch)
{
    auto context = static_cast<AppContext*>(ctx);
    auto rpcResult = context->rpc.Call("shutup_all_member", [&](TWriter& writer)
        {
            writer.StartArray();
            writer.String(EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(bot)));
            writer.String(EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(source)));
            writer.Bool(shutupSwitch);
            writer.EndArray();
        });
}

Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetMemberName)(void* ctx, Encoding::ConstStr bot, Encoding::ConstStr source, Encoding::ConstStr target)
{
    auto context = static_cast<AppContext*>(ctx);
    auto rpcResult = context->rpc.Call("get_user_avatar", [&](TWriter& writer)
        {
            writer.StartArray();
            writer.String(EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(bot)));
            writer.String(EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(source)));
            writer.String(EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(target)));
            writer.EndArray();
        });
    auto result = rpcResult.Result.IsString() ? rpcResult.Result.GetString() : nullptr;
    static auto data = EncodingImpl::PermTo_S(result);
    return EncodingImpl::PermTo_G(data);
}

Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetUserAvatar)(void* ctx, Encoding::ConstStr bot, Encoding::ConstStr id)
{
    auto context = static_cast<AppContext*>(ctx);
    auto rpcResult = context->rpc.Call("get_user_avatar", [&](TWriter& writer)
        {
            writer.StartArray();
            writer.String(EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(bot)));
            writer.String(EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(id)));
            writer.EndArray();
        });
    auto result = rpcResult.Result.IsString() ? rpcResult.Result.GetString() : nullptr;
    static auto data = EncodingImpl::PermTo_S(result);
    return EncodingImpl::PermTo_G(data);
}

Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetSelfID)(void* ctx, Encoding::ConstStr bot)
{
    auto context = static_cast<AppContext*>(ctx);
    auto rpcResult = context->rpc.Call("get_self_id", [&](TWriter& writer)
        {
            writer.StartArray();
            writer.String(EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(bot)));
            writer.EndArray();
        });
    auto result = rpcResult.Result.IsString() ? rpcResult.Result.GetString() : nullptr;
    static auto data = EncodingImpl::PermTo_S(result);
    return EncodingImpl::PermTo_G(data);
}

Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetPlatformID)(void* ctx, Encoding::ConstStr bot)
{
    auto context = static_cast<AppContext*>(ctx);
    auto rpcResult = context->rpc.Call("get_platform_id", [&](TWriter& writer)
        {
            writer.StartArray();
            writer.String(EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(bot)));
            writer.EndArray();
        });
    auto result = rpcResult.Result.IsString() ? rpcResult.Result.GetString() : nullptr;
    static auto data = EncodingImpl::PermTo_S(result);
    return EncodingImpl::PermTo_G(data);
}

Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetGroupList)(void* ctx, Encoding::ConstStr bot)
{
    auto context = static_cast<AppContext*>(ctx);
    auto rpcResult = context->rpc.Call("get_group_list", [&](TWriter& writer)
        {
            writer.StartArray();
            writer.String(EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(bot)));
            writer.EndArray();
        });
    static auto data = EncodingImpl::PermTo_S(fromStringArray(rpcResult.Result, "|").c_str());
    return EncodingImpl::PermTo_G(data);
}

Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetMemberList)(void* ctx, Encoding::ConstStr bot, Encoding::ConstStr id)
{
    auto context = static_cast<AppContext*>(ctx);
    auto rpcResult = context->rpc.Call("get_member_list", [&](TWriter& writer)
        {
            writer.StartArray();
            writer.String(EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(bot)));
            writer.String(EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(id)));
            writer.EndArray();
        });
    static auto data = EncodingImpl::PermTo_S(fromStringArray(rpcResult.Result, "|").c_str());
    return EncodingImpl::PermTo_G(data);
}

void __stdcall UNativeStr_WithSuffix(ubotAppSetOnReceiveChatMessageHandler)(void* ctx, void* user,
    EventResultType(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr bot, ChatMessageType type, Encoding::ConstStr source, Encoding::ConstStr sender, Encoding::ConstStr message, Encoding::ConstStr info))
{
    auto context = static_cast<AppContext*>(ctx);
    context->rpc.SetHandler("on_receive_chat_message", [ctx, user, handler](rapidjson::Value&& params, TWriter& writer)
        {
            const char* bot;
            int type;
            const char* source;
            const char* sender;
            const char* message;
            const rapidjson::Value* info;
            ReadParam(params, 0, "bot", &bot);
            ReadParam(params, 1, "type", &type);
            ReadParam(params, 2, "source", &source);
            ReadParam(params, 3, "sender", &sender);
            ReadParam(params, 4, "message", &message);
            ReadRawParam(params, 5, "info", &info);

            rapidjson::GenericStringBuffer<rapidjson::UTF8<> > infoText;
            TWriter infoWriter(infoText);
            infoWriter.Flush();

            auto result = handler(
                ctx,
                user,
                EncodingImpl::TempTo_G(EncodingImpl::TempTo_S(bot)),
                static_cast<ChatMessageType>(type),
                EncodingImpl::TempTo_G(EncodingImpl::TempTo_S(source)),
                EncodingImpl::TempTo_G(EncodingImpl::TempTo_S(sender)),
                EncodingImpl::TempTo_G(EncodingImpl::TempTo_S(message)),
                EncodingImpl::TempTo_G(EncodingImpl::TempTo_S(infoText.GetString())));

            WriteEventResult(writer, result);
        });
}

void __stdcall UNativeStr_WithSuffix(ubotAppSetOnMemberJoinedHandler)(void* ctx, void* user,
    EventResultType(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr bot, Encoding::ConstStr source, Encoding::ConstStr sender, Encoding::ConstStr inviter))
{
    auto context = static_cast<AppContext*>(ctx);
    context->rpc.SetHandler("on_member_joined", [ctx, user, handler](rapidjson::Value&& params, TWriter& writer)
        {
            const char* bot;
            const char* source;
            const char* sender;
            const char* inviter;
            ReadParam(params, 0, "bot", &bot);
            ReadParam(params, 1, "source", &source);
            ReadParam(params, 2, "sender", &sender);
            ReadParam(params, 3, "inviter", &inviter);

            auto result = handler(
                ctx,
                user,
                EncodingImpl::TempTo_G(EncodingImpl::TempTo_S(bot)),
                EncodingImpl::TempTo_G(EncodingImpl::TempTo_S(source)),
                EncodingImpl::TempTo_G(EncodingImpl::TempTo_S(sender)),
                EncodingImpl::TempTo_G(EncodingImpl::TempTo_S(inviter)));

            WriteEventResult(writer, result);
        });
}

void __stdcall UNativeStr_WithSuffix(ubotAppSetOnMemberLeftHandler)(void* ctx, void* user,
    EventResultType(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr bot, Encoding::ConstStr source, Encoding::ConstStr sender))
{
    auto context = static_cast<AppContext*>(ctx);
    context->rpc.SetHandler("on_member_left", [handler, ctx, user](rapidjson::Value&& params, TWriter& writer)
        {
            const char* bot;
            const char* source;
            const char* sender;
            ReadParam(params, 0, "bot", &bot);
            ReadParam(params, 1, "source", &source);
            ReadParam(params, 2, "sender", &sender);

            auto result = handler(
                ctx,
                user,
                EncodingImpl::TempTo_G(EncodingImpl::TempTo_S(bot)),
                EncodingImpl::TempTo_G(EncodingImpl::TempTo_S(source)),
                EncodingImpl::TempTo_G(EncodingImpl::TempTo_S(sender)));

            WriteEventResult(writer, result);
        });
}

void __stdcall UNativeStr_WithSuffix(ubotAppSetProcessGroupInvitationHandler)(void* ctx, void* user,
    EventResultType(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr bot, Encoding::ConstStr sender, Encoding::ConstStr target, Encoding::ConstStr reason, Encoding::Str respondedReason))
{
    auto context = static_cast<AppContext*>(ctx);
    context->rpc.SetHandler("process_group_invitation", [handler, ctx, user](rapidjson::Value&& params, TWriter& writer)
        {
            const char* bot;
            const char* sender;
            const char* target;
            const char* reason;
            ReadParam(params, 0, "bot", &bot);
            ReadParam(params, 1, "sender", &sender);
            ReadParam(params, 2, "target", &target);
            ReadParam(params, 3, "reason", &reason);

            Encoding::Char buf[UNativeBufferSize];
            buf[0] = '\0';

            auto result = handler(
                ctx,
                user,
                EncodingImpl::TempTo_G(EncodingImpl::TempTo_S(bot)),
                EncodingImpl::TempTo_G(EncodingImpl::TempTo_S(sender)),
                EncodingImpl::TempTo_G(EncodingImpl::TempTo_S(target)),
                EncodingImpl::TempTo_G(EncodingImpl::TempTo_S(reason)),
                buf);

            WriteEventResultWithReason(writer, result, buf);
        });
}

void __stdcall UNativeStr_WithSuffix(ubotAppSetProcessFriendRequestHandler)(void* ctx, void* user,
    EventResultType(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr bot, Encoding::ConstStr sender, Encoding::ConstStr reason, Encoding::Str respondedReason))
{
    auto context = static_cast<AppContext*>(ctx);
    context->rpc.SetHandler("process_friend_request", [handler, ctx, user](rapidjson::Value&& params, TWriter& writer)
        {
            const char* bot;
            const char* sender;
            const char* reason;
            ReadParam(params, 0, "bot", &bot);
            ReadParam(params, 1, "sender", &sender);
            ReadParam(params, 2, "reason", &reason);

            Encoding::Char buf[UNativeBufferSize];
            buf[0] = '\0';

            auto result = handler(
                ctx,
                user,
                EncodingImpl::TempTo_G(EncodingImpl::TempTo_S(bot)),
                EncodingImpl::TempTo_G(EncodingImpl::TempTo_S(sender)),
                EncodingImpl::TempTo_G(EncodingImpl::TempTo_S(reason)),
                buf);

            WriteEventResultWithReason(writer, result, buf);
        });
}

void __stdcall UNativeStr_WithSuffix(ubotAppSetProcessMembershipRequestHandler)(void* ctx, void* user,
    EventResultType(__stdcall* handler)(void* ctx, void* user, Encoding::ConstStr bot, Encoding::ConstStr source, Encoding::ConstStr sender, Encoding::ConstStr inviter, Encoding::ConstStr reason, Encoding::Str respondedReason))
{
    auto context = static_cast<AppContext*>(ctx);
    context->rpc.SetHandler("process_membership_request", [handler, ctx, user](rapidjson::Value&& params, TWriter& writer)
        {
            const char* bot;
            const char* source;
            const char* sender;
            const char* inviter;
            const char* reason;
            ReadParam(params, 0, "bot", &bot);
            ReadParam(params, 1, "source", &source);
            ReadParam(params, 2, "sender", &sender);
            ReadParam(params, 3, "inviter", &inviter);
            ReadParam(params, 4, "reason", &reason);

            Encoding::Char buf[UNativeBufferSize];
            buf[0] = '\0';

            auto result = handler(
                ctx,
                user,
                EncodingImpl::TempTo_G(EncodingImpl::TempTo_S(bot)),
                EncodingImpl::TempTo_G(EncodingImpl::TempTo_S(source)),
                EncodingImpl::TempTo_G(EncodingImpl::TempTo_S(sender)),
                EncodingImpl::TempTo_G(EncodingImpl::TempTo_S(inviter)),
                EncodingImpl::TempTo_G(EncodingImpl::TempTo_S(reason)),
                buf);

            WriteEventResultWithReason(writer, result, buf);
        });
}


void __stdcall UNativeStr_WithSuffix(ubotAppHost)(
    void* ctx,
    Encoding::ConstStr op,
    Encoding::ConstStr urlStr,
    Encoding::ConstStr id)
{
    auto context = static_cast<AppContext*>(ctx);
    HostUBotClient(EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(op)), 
        EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(urlStr)), &context->rpc,
        [=](const skyr::url& managerUrl, JsonRpc& rpc) -> std::string {
            auto clientUrl = managerUrl;
            std::string clientTken;
            auto registered = rpc.Call("register_app", [&](TWriter& writer)
                {
                    writer.StartArray();
                    writer.String(EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(id)));
                    writer.EndArray();
                });
            if (registered.Error.has_value())
            {
                return "";
            }
            clientUrl.set_pathname("/api/app");
            clientUrl.set_search("?id=" + skyr::percent_encode(std::string(EncodingImpl::TempFrom_G(EncodingImpl::TempFrom_S(id)))) + "&token=" + registered.Result.GetString());
            return clientUrl.href();
        }, context->startup);
}