#include "AppHost.h"
#include "UNativeStrHelper.h"
#include <skyr/percent_encoding/percent_encode.hpp>
#include "UBotClientHost.h"
inline ubot::JsonRpc* appApi = nullptr;

inline EventResultType __stdcall DefaultOnReceiveChatMessage(UNativeStr bot, ChatMessageType type, UNativeStr source, UNativeStr sender, UNativeStr message, UNativeStr info)
{
    return EventResultType::Ignore;
}
inline EventResultType __stdcall DefaultOnMemberJoined(UNativeStr bot, UNativeStr source, UNativeStr sender, UNativeStr inviter)
{
    return EventResultType::Ignore;
}
inline EventResultType __stdcall DefaultOnMemberLeft(UNativeStr bot, UNativeStr source, UNativeStr sender)
{
    return EventResultType::Ignore;
}
inline EventResultType __stdcall DefaultProcessGroupInvitation(UNativeStr bot, UNativeStr sender, UNativeStr target, UNativeStr reason, UNativeChar* respondedReason)
{
    return EventResultType::Ignore;
}
inline EventResultType __stdcall DefaultProcessFriendRequest(UNativeStr bot, UNativeStr sender, UNativeStr reason, UNativeChar* respondedReason)
{
    return EventResultType::Ignore;
}
inline EventResultType __stdcall DefaultProcessMembershipRequest(UNativeStr bot, UNativeStr source, UNativeStr sender, UNativeStr inviter, UNativeStr reason, UNativeChar* respondedReason)
{
    return EventResultType::Ignore;
}
inline void DefaultStartup()
{

}

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

UNativeStr __stdcall UNativeStr_WithSuffix(app_GetGroupName)(UNativeStr bot, UNativeStr id)
{
    auto rpcResult = appApi->Call("get_group_name", [&](ubot::TWriter& writer)
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

UNativeStr __stdcall UNativeStr_WithSuffix(app_GetUserName)(UNativeStr bot, UNativeStr id)
{
    auto rpcResult = appApi->Call("get_user_name", [&](ubot::TWriter& writer)
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

void __stdcall UNativeStr_WithSuffix(app_SendChatMessage)(UNativeStr bot, ChatMessageType type, UNativeStr source, UNativeStr target, UNativeStr message)
{
    auto rpcResult = appApi->Call("send_chat_message", [&](ubot::TWriter& writer)
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

void __stdcall UNativeStr_WithSuffix(app_RemoveMember)(UNativeStr bot, UNativeStr source, UNativeStr target)
{
    auto rpcResult = appApi->Call("remove_member", [&](ubot::TWriter& writer)
        {
            writer.StartArray();
            writer.String(FromNativeString(bot));
            writer.String(FromNativeString(source));
            writer.String(FromNativeString(target));
            writer.EndArray();
        });
}

void __stdcall UNativeStr_WithSuffix(app_ShutupMember)(UNativeStr bot, UNativeStr source, UNativeStr target, int duration)
{
    auto rpcResult = appApi->Call("shutup_member", [&](ubot::TWriter& writer)
        {
            writer.StartArray();
            writer.String(FromNativeString(bot));
            writer.String(FromNativeString(source));
            writer.String(FromNativeString(target));
            writer.Int(duration);
            writer.EndArray();
        });
}

void __stdcall UNativeStr_WithSuffix(app_ShutupAllMember)(UNativeStr bot, UNativeStr source, bool shutupSwitch)
{
    auto rpcResult = appApi->Call("shutup_all_member", [&](ubot::TWriter& writer)
        {
            writer.StartArray();
            writer.String(FromNativeString(bot));
            writer.String(FromNativeString(source));
            writer.Bool(shutupSwitch);
            writer.EndArray();
        });
}

UNativeStr __stdcall UNativeStr_WithSuffix(app_GetMemberName)(UNativeStr bot, UNativeStr source, UNativeStr target)
{
    auto rpcResult = appApi->Call("get_user_avatar", [&](ubot::TWriter& writer)
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

UNativeStr __stdcall UNativeStr_WithSuffix(app_GetUserAvatar)(UNativeStr bot, UNativeStr id)
{
    auto rpcResult = appApi->Call("get_user_avatar", [&](ubot::TWriter& writer)
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

UNativeStr __stdcall UNativeStr_WithSuffix(app_GetSelfID)(UNativeStr bot)
{
    auto rpcResult = appApi->Call("get_self_id", [&](ubot::TWriter& writer)
        {
            writer.StartArray();
            writer.String(FromNativeString(bot));
            writer.EndArray();
        });
    auto result = rpcResult.Result.IsString() ? rpcResult.Result.GetString() : nullptr;
    static auto data = ToPermanentNativeString(result);
    return GetPermanentNativeString(data);
}

UNativeStr __stdcall UNativeStr_WithSuffix(app_GetPlatformID)(UNativeStr bot)
{
    auto rpcResult = appApi->Call("get_platform_id", [&](ubot::TWriter& writer)
        {
            writer.StartArray();
            writer.String(FromNativeString(bot));
            writer.EndArray();
        });
    auto result = rpcResult.Result.IsString() ? rpcResult.Result.GetString() : nullptr;
    static auto data = ToPermanentNativeString(result);
    return GetPermanentNativeString(data);
}

UNativeStr __stdcall UNativeStr_WithSuffix(app_GetGroupList)(UNativeStr bot)
{
    auto rpcResult = appApi->Call("get_group_list", [&](ubot::TWriter& writer)
        {
            writer.StartArray();
            writer.String(FromNativeString(bot));
            writer.EndArray();
        });
    static auto data = ToPermanentNativeString(fromStringArray(rpcResult.Result, "|").c_str());
    return GetPermanentNativeString(data);
}

UNativeStr __stdcall UNativeStr_WithSuffix(app_GetMemberList)(UNativeStr bot, UNativeStr id)
{
    auto rpcResult = appApi->Call("get_member_list", [&](ubot::TWriter& writer)
        {
            writer.StartArray();
            writer.String(FromNativeString(bot));
            writer.String(FromNativeString(id));
            writer.EndArray();
        });
    static auto data = ToPermanentNativeString(fromStringArray(rpcResult.Result, "|").c_str());
    return GetPermanentNativeString(data);
}

void __stdcall UNativeStr_WithSuffix(app_Host)(
    UNativeStr op,
    UNativeStr urlStr,
    UNativeStr id,
    void (*startup)(),
    const UNativeStr_WithSuffix(AppHandler)* handler)
{
#define MinSize(t,m) offsetof(t, m) + sizeof(((t*)0)->m)
#define ReadEventHandler(to, from) auto to = \
    (handler->Size >= MinSize(UNativeStr_WithSuffix(AppHandler), from)) \
    && (handler->from != nullptr) \
    ? handler->from \
    : &Default##from

    ReadEventHandler(onReceiveChatMessage, OnReceiveChatMessage);
    ReadEventHandler(onMemberJoined, OnMemberJoined);
    ReadEventHandler(onMemberLeft, OnMemberLeft);
    ReadEventHandler(processFriendRequest, ProcessFriendRequest);
    ReadEventHandler(processGroupInvitation, ProcessGroupInvitation);
    ReadEventHandler(processMembershipRequest, ProcessMembershipRequest);
    ubot::HostUBotClient(FromNativeString(op), FromNativeString(urlStr),
        [=](const skyr::url& managerUrl, ubot::JsonRpc& rpc) -> std::string
        {
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
            clientUrl.set_search("?id=" + skyr::percent_encode<std::string>(FromNativeString(id)) + "&token=" + registered.Result.GetString());
            return clientUrl.href();
        },
        [=](ubot::JsonRpc& rpc)
        {
            appApi = &rpc;
            rpc.Register("on_receive_chat_message", [onReceiveChatMessage](rapidjson::Value&& params, ubot::TWriter& writer)
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

                    auto result = onReceiveChatMessage(
                        ToNativeString(bot),
                        static_cast<ChatMessageType>(type),
                        ToNativeString(source),
                        ToNativeString(sender),
                        ToNativeString(message),
                        ToNativeString(infoText.GetString()));

                    WriteEventResult(writer, result);
                });
            rpc.Register("on_member_joined", [onMemberJoined](rapidjson::Value&& params, ubot::TWriter& writer)
                {
                    const char* bot;
                    const char* source;
                    const char* sender;
                    const char* inviter;
                    ubot::ReadParam(params, 0, "bot", &bot);
                    ubot::ReadParam(params, 1, "source", &source);
                    ubot::ReadParam(params, 2, "sender", &sender);
                    ubot::ReadParam(params, 3, "inviter", &inviter);

                    auto result = onMemberJoined(
                        ToNativeString(bot),
                        ToNativeString(source),
                        ToNativeString(sender),
                        ToNativeString(inviter));

                    WriteEventResult(writer, result);
                });
            rpc.Register("on_member_left", [onMemberLeft](rapidjson::Value&& params, ubot::TWriter& writer)
                {
                    const char* bot;
                    const char* source;
                    const char* sender;
                    ubot::ReadParam(params, 0, "bot", &bot);
                    ubot::ReadParam(params, 1, "source", &source);
                    ubot::ReadParam(params, 2, "sender", &sender);

                    auto result = onMemberLeft(
                        ToNativeString(bot),
                        ToNativeString(source),
                        ToNativeString(sender));

                    WriteEventResult(writer, result);
                });
            rpc.Register("process_group_invitation", [processGroupInvitation](rapidjson::Value&& params, ubot::TWriter& writer)
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

                    auto result = processGroupInvitation(
                        ToNativeString(bot),
                        ToNativeString(sender),
                        ToNativeString(target),
                        ToNativeString(reason),
                        buf);

                    WriteEventResultWithReason(writer, result, buf);
                });
            rpc.Register("process_friend_request", [processFriendRequest](rapidjson::Value&& params, ubot::TWriter& writer)
                {
                    const char* bot;
                    const char* sender;
                    const char* reason;
                    ubot::ReadParam(params, 0, "bot", &bot);
                    ubot::ReadParam(params, 1, "sender", &sender);
                    ubot::ReadParam(params, 2, "reason", &reason);

                    UNativeChar buf[UNativeBufferSize];
                    buf[0] = '\0';

                    auto result = processFriendRequest(
                        ToNativeString(bot),
                        ToNativeString(sender),
                        ToNativeString(reason),
                        buf);

                    WriteEventResultWithReason(writer, result, buf);
                });
            rpc.Register("process_membership_request", [processMembershipRequest](rapidjson::Value&& params, ubot::TWriter& writer)
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

                    auto result = processMembershipRequest(
                        ToNativeString(bot),
                        ToNativeString(source),
                        ToNativeString(sender),
                        ToNativeString(inviter),
                        ToNativeString(reason),
                        buf);

                    WriteEventResultWithReason(writer, result, buf);
                });
        }, startup ? startup : &DefaultStartup);
}