#pragma once
#include "UNativeStr.h"
extern "C"
{
	enum class ChatMessageType
	{
		Group,
		Private
	};
	enum class EventResultType
	{
		Ignore = 0,
		Continue = 1,
		Complete = 2,
		AcceptRequest = 10,
		RejectRequest = 20
	};
	struct UNativeStr_WithSuffix(AppHandler)
	{
		size_t Size;
		EventResultType(__stdcall * OnReceiveChatMessage)(UNativeStr bot, ChatMessageType type, UNativeStr source, UNativeStr sender, UNativeStr message, UNativeStr info);
		EventResultType(__stdcall * OnMemberJoined)(UNativeStr bot, UNativeStr source, UNativeStr sender, UNativeStr inviter);
		EventResultType(__stdcall * OnMemberLeft)(UNativeStr bot, UNativeStr source, UNativeStr sender);
		EventResultType(__stdcall * ProcessGroupInvitation)(UNativeStr bot, UNativeStr sender, UNativeStr target, UNativeStr reason, UNativeChar *respondedReason);
		EventResultType(__stdcall * ProcessFriendRequest)(UNativeStr bot, UNativeStr sender, UNativeStr reason, UNativeChar * respondedReason);
		EventResultType(__stdcall * ProcessMembershipRequest)(UNativeStr bot, UNativeStr source, UNativeStr sender, UNativeStr inviter, UNativeStr reason, UNativeChar * respondedReason);
	};
	void __stdcall UNativeStr_WithSuffix(app_Host)(UNativeStr op, UNativeStr urlStr, UNativeStr name, void (*startup)(), const UNativeStr_WithSuffix(AppHandler)* handler);
	UNativeStr __stdcall UNativeStr_WithSuffix(app_GetGroupName)(UNativeStr bot, UNativeStr id);
	UNativeStr __stdcall UNativeStr_WithSuffix(app_GetUserName)(UNativeStr bot, UNativeStr id);
	void __stdcall UNativeStr_WithSuffix(app_SendChatMessage)(UNativeStr bot, ChatMessageType type, UNativeStr source, UNativeStr target, UNativeStr message);
	void __stdcall UNativeStr_WithSuffix(app_RemoveMember)(UNativeStr bot, UNativeStr source, UNativeStr target);
	void __stdcall UNativeStr_WithSuffix(app_ShutupMember)(UNativeStr bot, UNativeStr source, UNativeStr target, int duration);
	void __stdcall UNativeStr_WithSuffix(app_ShutupAllMember)(UNativeStr bot, UNativeStr source, bool shutupSwitch);
	UNativeStr __stdcall UNativeStr_WithSuffix(app_GetMemberName)(UNativeStr bot, UNativeStr source, UNativeStr target);
	UNativeStr __stdcall UNativeStr_WithSuffix(app_GetUserAvatar)(UNativeStr bot, UNativeStr id);
	UNativeStr __stdcall UNativeStr_WithSuffix(app_GetSelfID)(UNativeStr bot);
	UNativeStr __stdcall UNativeStr_WithSuffix(app_GetPlatformID)(UNativeStr bot);
	UNativeStr __stdcall UNativeStr_WithSuffix(app_GetGroupList)(UNativeStr bot);
	UNativeStr __stdcall UNativeStr_WithSuffix(app_GetMemberList)(UNativeStr bot, UNativeStr id);
}

typedef UNativeStr_WithSuffix(AppHandler) AppHandler;
inline auto& app_Host = UNativeStr_WithSuffix(app_Host);
inline auto& app_GetGroupName = UNativeStr_WithSuffix(app_GetGroupName);
inline auto& app_GetUserName = UNativeStr_WithSuffix(app_GetUserName);
inline auto& app_SendChatMessage = UNativeStr_WithSuffix(app_SendChatMessage);
inline auto& app_RemoveMember = UNativeStr_WithSuffix(app_RemoveMember);
inline auto& app_ShutupMember = UNativeStr_WithSuffix(app_ShutupMember);
inline auto& app_ShutupAllMember = UNativeStr_WithSuffix(app_ShutupAllMember);
inline auto& app_GetMemberName = UNativeStr_WithSuffix(app_GetMemberName);
inline auto& app_GetUserAvatar = UNativeStr_WithSuffix(app_GetUserAvatar);
inline auto& app_GetSelfID = UNativeStr_WithSuffix(app_GetSelfID);
inline auto& app_GetPlatformID = UNativeStr_WithSuffix(app_GetPlatformID);
inline auto& app_GetGroupList = UNativeStr_WithSuffix(app_GetGroupList);
inline auto& app_GetMemberList = UNativeStr_WithSuffix(app_GetMemberList);