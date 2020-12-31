#include <skyr/percent_encoding/percent_encode.hpp>
#include "UBotClientHost.h"
#include "AppHost.h"
#include "UNativeStrHelper.h"
#include "UBotAppContext.h"

inline void WriteEventResult(ubot::TWriter& writer, EventResultType type)
{
    ubot::JsonRpc::StartResult(writer);
    writer.StartObject();
    writer.Key("type");
    writer.Int(static_cast<int>(type));
    writer.EndObject();
    ubot::JsonRpc::EndResult(writer);
}

inline void WriteEventResultWithReason(ubot::TWriter& writer, EventResultType type, UNativeStr reason)
{
    ubot::JsonRpc::StartResult(writer);
    writer.StartObject();
    writer.Key("type");
    writer.Int(static_cast<int>(type));
    writer.Key("reason");
    writer.String(FromNativeString(reason));
    writer.EndObject();
    ubot::JsonRpc::EndResult(writer);
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

UNativeStr __stdcall UNativeStr_WithSuffix(ubotAppGetGroupName)(void* ctx, UNativeStr bot, UNativeStr id)
{
    auto context = static_cast<ubot::AppContext*>(ctx);
    auto rpcResult = context->rpc.Call("get_group_name", [&](ubot::TWriter& writer)
        {
            writer.StartArray();
            writer.String(FromNativeString(bot));
            writer.String(FromNativeString(id));
            writer.EndArray();
        });
    auto result = rpcResult.Result.IsString() ? rpcResult.Result.GetString() : nullptr;
    static auto data = ToPermanentNativeString(result);
    return GetPermanentNativeString(data);
}

UNativeStr __stdcall UNativeStr_WithSuffix(ubotAppGetUserName)(void* ctx, UNativeStr bot, UNativeStr id)
{
    auto context = static_cast<ubot::AppContext*>(ctx);
    auto rpcResult = context->rpc.Call("get_user_name", [&](ubot::TWriter& writer)
        {
            writer.StartArray();
            writer.String(FromNativeString(bot));
            writer.String(FromNativeString(id));
            writer.EndArray();
        });
    auto result = rpcResult.Result.IsString() ? rpcResult.Result.GetString() : nullptr;
    static auto data = ToPermanentNativeString(result);
    return GetPermanentNativeString(data);
}

void __stdcall UNativeStr_WithSuffix(ubotAppSendChatMessage)(void* ctx, UNativeStr bot, ChatMessageType type, UNativeStr source, UNativeStr target, UNativeStr message)
{
    auto context = static_cast<ubot::AppContext*>(ctx);
    auto rpcResult = context->rpc.Call("send_chat_message", [&](ubot::TWriter& writer)
        {
            writer.StartArray();
            writer.String(FromNativeString(bot));
            writer.Int(static_cast<int>(type));
            writer.String(FromNativeString(source));
            writer.String(FromNativeString(target));
            writer.String(FromNativeString(message));
            writer.EndArray();
        });
}

void __stdcall UNativeStr_WithSuffix(ubotAppRemoveMember)(void* ctx, UNativeStr bot, UNativeStr source, UNativeStr target)
{
    auto context = static_cast<ubot::AppContext*>(ctx);
    auto rpcResult = context->rpc.Call("remove_member", [&](ubot::TWriter& writer)
        {
            writer.StartArray();
            writer.String(FromNativeString(bot));
            writer.String(FromNativeString(source));
            writer.String(FromNativeString(target));
            writer.EndArray();
        });
}

void __stdcall UNativeStr_WithSuffix(ubotAppShutupMember)(void* ctx, UNativeStr bot, UNativeStr source, UNativeStr target, int duration)
{
    auto context = static_cast<ubot::AppContext*>(ctx);
    auto rpcResult = context->rpc.Call("shutup_member", [&](ubot::TWriter& writer)
        {
            writer.StartArray();
            writer.String(FromNativeString(bot));
            writer.String(FromNativeString(source));
            writer.String(FromNativeString(target));
            writer.Int(duration);
            writer.EndArray();
        });
}

void __stdcall UNativeStr_WithSuffix(ubotAppShutupAllMember)(void* ctx, UNativeStr bot, UNativeStr source, bool shutupSwitch)
{
    auto context = static_cast<ubot::AppContext*>(ctx);
    auto rpcResult = context->rpc.Call("shutup_all_member", [&](ubot::TWriter& writer)
        {
            writer.StartArray();
            writer.String(FromNativeString(bot));
            writer.String(FromNativeString(source));
            writer.Bool(shutupSwitch);
            writer.EndArray();
        });
}

UNativeStr __stdcall UNativeStr_WithSuffix(ubotAppGetMemberName)(void* ctx, UNativeStr bot, UNativeStr source, UNativeStr target)
{
    auto context = static_cast<ubot::AppContext*>(ctx);
    auto rpcResult = context->rpc.Call("get_user_avatar", [&](ubot::TWriter& writer)
        {
            writer.StartArray();
            writer.String(FromNativeString(bot));
            writer.String(FromNativeString(source));
            writer.String(FromNativeString(target));
            writer.EndArray();
        });
    auto result = rpcResult.Result.IsString() ? rpcResult.Result.GetString() : nullptr;
    static auto data = ToPermanentNativeString(result);
    return GetPermanentNativeString(data);
}

UNativeStr __stdcall UNativeStr_WithSuffix(ubotAppGetUserAvatar)(void* ctx, UNativeStr bot, UNativeStr id)
{
    auto context = static_cast<ubot::AppContext*>(ctx);
    auto rpcResult = context->rpc.Call("get_user_avatar", [&](ubot::TWriter& writer)
        {
            writer.StartArray();
            writer.String(FromNativeString(bot));
            writer.String(FromNativeString(id));
            writer.EndArray();
        });
    auto result = rpcResult.Result.IsString() ? rpcResult.Result.GetString() : nullptr;
    static auto data = ToPermanentNativeString(result);
    return GetPermanentNativeString(data);
}

UNativeStr __stdcall UNativeStr_WithSuffix(ubotAppGetSelfID)(void* ctx, UNativeStr bot)
{
    auto context = static_cast<ubot::AppContext*>(ctx);
    auto rpcResult = context->rpc.Call("get_self_id", [&](ubot::TWriter& writer)
        {
            writer.StartArray();
            writer.String(FromNativeString(bot));
            writer.EndArray();
        });
    auto result = rpcResult.Result.IsString() ? rpcResult.Result.GetString() : nullptr;
    static auto data = ToPermanentNativeString(result);
    return GetPermanentNativeString(data);
}

UNativeStr __stdcall UNativeStr_WithSuffix(ubotAppGetPlatformID)(void* ctx, UNativeStr bot)
{
    auto context = static_cast<ubot::AppContext*>(ctx);
    auto rpcResult = context->rpc.Call("get_platform_id", [&](ubot::TWriter& writer)
        {
            writer.StartArray();
            writer.String(FromNativeString(bot));
            writer.EndArray();
        });
    auto result = rpcResult.Result.IsString() ? rpcResult.Result.GetString() : nullptr;
    static auto data = ToPermanentNativeString(result);
    return GetPermanentNativeString(data);
}

UNativeStr __stdcall UNativeStr_WithSuffix(ubotAppGetGroupList)(void* ctx, UNativeStr bot)
{
    auto context = static_cast<ubot::AppContext*>(ctx);
    auto rpcResult = context->rpc.Call("get_group_list", [&](ubot::TWriter& writer)
        {
            writer.StartArray();
            writer.String(FromNativeString(bot));
            writer.EndArray();
        });
    static auto data = ToPermanentNativeString(fromStringArray(rpcResult.Result, "|").c_str());
    return GetPermanentNativeString(data);
}

UNativeStr __stdcall UNativeStr_WithSuffix(ubotAppGetMemberList)(void* ctx, UNativeStr bot, UNativeStr id)
{
    auto context = static_cast<ubot::AppContext*>(ctx);
    auto rpcResult = context->rpc.Call("get_member_list", [&](ubot::TWriter& writer)
        {
            writer.StartArray();
            writer.String(FromNativeString(bot));
            writer.String(FromNativeString(id));
            writer.EndArray();
        });
    static auto data = ToPermanentNativeString(fromStringArray(rpcResult.Result, "|").c_str());
    return GetPermanentNativeString(data);
}

void __stdcall UNativeStr_WithSuffix(ubotAppSetOnReceiveChatMessageHandler)(void* ctx, void* user,
    EventResultType(__stdcall* handler)(void* ctx, void* user, UNativeStr bot, ChatMessageType type, UNativeStr source, UNativeStr sender, UNativeStr message, UNativeStr info))
{
    auto context = static_cast<ubot::AppContext*>(ctx);
    context->rpc.SetHandler("on_receive_chat_message", [ctx, user, handler](rapidjson::Value&& params, ubot::TWriter& writer)
        {
            const char* bot;
            int type;
            const char* source;
            const char* sender;
            const char* message;
            const rapidjson::Value* info;
            ubot::ReadParam(params, 0, "bot", &bot);
            ubot::ReadParam(params, 1, "type", &type);
            ubot::ReadParam(params, 2, "source", &source);
            ubot::ReadParam(params, 3, "sender", &sender);
            ubot::ReadParam(params, 4, "message", &message);
            ubot::ReadRawParam(params, 5, "info", &info);

            rapidjson::GenericStringBuffer<rapidjson::UTF8<> > infoText;
            ubot::TWriter infoWriter(infoText);
            infoWriter.Flush();

            auto result = handler(
                ctx,
                user,
                ToNativeString(bot),
                static_cast<ChatMessageType>(type),
                ToNativeString(source),
                ToNativeString(sender),
                ToNativeString(message),
                ToNativeString(infoText.GetString()));

            WriteEventResult(writer, result);
        });
}

void __stdcall UNativeStr_WithSuffix(ubotAppSetOnMemberJoinedHandler)(void* ctx, void* user,
    EventResultType(__stdcall* handler)(void* ctx, void* user, UNativeStr bot, UNativeStr source, UNativeStr sender, UNativeStr inviter))
{
    auto context = static_cast<ubot::AppContext*>(ctx);
    context->rpc.SetHandler("on_member_joined", [ctx, user, handler](rapidjson::Value&& params, ubot::TWriter& writer)
        {
            const char* bot;
            const char* source;
            const char* sender;
            const char* inviter;
            ubot::ReadParam(params, 0, "bot", &bot);
            ubot::ReadParam(params, 1, "source", &source);
            ubot::ReadParam(params, 2, "sender", &sender);
            ubot::ReadParam(params, 3, "inviter", &inviter);

            auto result = handler(
                ctx,
                user,
                ToNativeString(bot),
                ToNativeString(source),
                ToNativeString(sender),
                ToNativeString(inviter));

            WriteEventResult(writer, result);
        });
}

void __stdcall UNativeStr_WithSuffix(ubotAppSetOnMemberLeftHandler)(void* ctx, void* user,
    EventResultType(__stdcall* handler)(void* ctx, void* user, UNativeStr bot, UNativeStr source, UNativeStr sender))
{
    auto context = static_cast<ubot::AppContext*>(ctx);
    context->rpc.SetHandler("on_member_left", [handler, ctx, user](rapidjson::Value&& params, ubot::TWriter& writer)
        {
            const char* bot;
            const char* source;
            const char* sender;
            ubot::ReadParam(params, 0, "bot", &bot);
            ubot::ReadParam(params, 1, "source", &source);
            ubot::ReadParam(params, 2, "sender", &sender);

            auto result = handler(
                ctx,
                user,
                ToNativeString(bot),
                ToNativeString(source),
                ToNativeString(sender));

            WriteEventResult(writer, result);
        });
}

void __stdcall UNativeStr_WithSuffix(ubotAppSetProcessGroupInvitationHandler)(void* ctx, void* user,
    EventResultType(__stdcall* handler)(void* ctx, void* user, UNativeStr bot, UNativeStr sender, UNativeStr target, UNativeStr reason, UNativeChar* respondedReason))
{
    auto context = static_cast<ubot::AppContext*>(ctx);
    context->rpc.SetHandler("process_group_invitation", [handler, ctx, user](rapidjson::Value&& params, ubot::TWriter& writer)
        {
            const char* bot;
            const char* sender;
            const char* target;
            const char* reason;
            ubot::ReadParam(params, 0, "bot", &bot);
            ubot::ReadParam(params, 1, "sender", &sender);
            ubot::ReadParam(params, 2, "target", &target);
            ubot::ReadParam(params, 3, "reason", &reason);

            UNativeChar buf[UNativeBufferSize];
            buf[0] = '\0';

            auto result = handler(
                ctx,
                user,
                ToNativeString(bot),
                ToNativeString(sender),
                ToNativeString(target),
                ToNativeString(reason),
                buf);

            WriteEventResultWithReason(writer, result, buf);
        });
}

void __stdcall UNativeStr_WithSuffix(ubotAppSetProcessFriendRequestHandler)(void* ctx, void* user,
    EventResultType(__stdcall* handler)(void* ctx, void* user, UNativeStr bot, UNativeStr sender, UNativeStr reason, UNativeChar* respondedReason))
{
    auto context = static_cast<ubot::AppContext*>(ctx);
    context->rpc.SetHandler("process_friend_request", [handler, ctx, user](rapidjson::Value&& params, ubot::TWriter& writer)
        {
            const char* bot;
            const char* sender;
            const char* reason;
            ubot::ReadParam(params, 0, "bot", &bot);
            ubot::ReadParam(params, 1, "sender", &sender);
            ubot::ReadParam(params, 2, "reason", &reason);

            UNativeChar buf[UNativeBufferSize];
            buf[0] = '\0';

            auto result = handler(
                ctx,
                user,
                ToNativeString(bot),
                ToNativeString(sender),
                ToNativeString(reason),
                buf);

            WriteEventResultWithReason(writer, result, buf);
        });
}

void __stdcall UNativeStr_WithSuffix(ubotAppSetProcessMembershipRequestHandler)(void* ctx, void* user,
    EventResultType(__stdcall* handler)(void* ctx, void* user, UNativeStr bot, UNativeStr source, UNativeStr sender, UNativeStr inviter, UNativeStr reason, UNativeChar* respondedReason))
{
    auto context = static_cast<ubot::AppContext*>(ctx);
    context->rpc.SetHandler("process_membership_request", [handler, ctx, user](rapidjson::Value&& params, ubot::TWriter& writer)
        {
            const char* bot;
            const char* source;
            const char* sender;
            const char* inviter;
            const char* reason;
            ubot::ReadParam(params, 0, "bot", &bot);
            ubot::ReadParam(params, 1, "source", &source);
            ubot::ReadParam(params, 2, "sender", &sender);
            ubot::ReadParam(params, 3, "inviter", &inviter);
            ubot::ReadParam(params, 4, "reason", &reason);

            UNativeChar buf[UNativeBufferSize];
            buf[0] = '\0';

            auto result = handler(
                ctx,
                user,
                ToNativeString(bot),
                ToNativeString(source),
                ToNativeString(sender),
                ToNativeString(inviter),
                ToNativeString(reason),
                buf);

            WriteEventResultWithReason(writer, result, buf);
        });
}


void __stdcall UNativeStr_WithSuffix(ubotAppHost)(
    void* ctx,
    UNativeStr op,
    UNativeStr urlStr,
    UNativeStr id)
{
    auto context = static_cast<ubot::AppContext*>(ctx);
    ubot::HostUBotClient(FromNativeString(op), FromNativeString(urlStr), &context->rpc,
        [=](const skyr::url& managerUrl, ubot::JsonRpc& rpc) -> std::string {
            auto clientUrl = managerUrl;
            std::string clientTken;
            auto registered = rpc.Call("register_app", [&](ubot::TWriter& writer)
                {
                    writer.StartArray();
                    writer.String(FromNativeString(id));
                    writer.EndArray();
                });
            if (registered.Error.has_value())
            {
                return "";
            }
            clientUrl.set_pathname("/api/app");
            clientUrl.set_search("?id=" + skyr::percent_encode(std::string(FromNativeString(id))) + "&token=" + registered.Result.GetString());
            return clientUrl.href();
        }, context->startup);
}