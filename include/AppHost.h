#pragma once
#include "EventResultType.h"
#include "ChatMessageType.h"
#include "UNativeStr.h"
extern "C"
{
	void* __stdcall ubotAppNew();
	void __stdcall ubotAppDelete(void* ctx);
	void __stdcall UNativeStr_WithSuffix(ubotAppSetOnReceiveChatMessageHandler)(void* ctx, void* user, EventResultType(__stdcall* handler)(void* ctx, void* user, ubot::Encoding::ConstStr bot, ChatMessageType type, ubot::Encoding::ConstStr source, ubot::Encoding::ConstStr sender, ubot::Encoding::ConstStr message, ubot::Encoding::ConstStr info));
	void __stdcall UNativeStr_WithSuffix(ubotAppSetOnReceiveChatMessageAsyncHandler)(void* ctx, void* user, EventResultType(__stdcall* handler)(void* ctx, void* user, ubot::Encoding::ConstStr bot, ChatMessageType type, ubot::Encoding::ConstStr source, ubot::Encoding::ConstStr sender, ubot::Encoding::ConstStr message, ubot::Encoding::ConstStr info, void* async_0, void* async_1));
	void __stdcall UNativeStr_WithSuffix(ubotAppSetOnMemberJoinedHandler)(void* ctx, void* user, EventResultType(__stdcall* handler)(void* ctx, void* user, ubot::Encoding::ConstStr bot, ubot::Encoding::ConstStr source, ubot::Encoding::ConstStr sender, ubot::Encoding::ConstStr inviter));
	void __stdcall UNativeStr_WithSuffix(ubotAppSetOnMemberJoinedAsyncHandler)(void* ctx, void* user, EventResultType(__stdcall* handler)(void* ctx, void* user, ubot::Encoding::ConstStr bot, ubot::Encoding::ConstStr source, ubot::Encoding::ConstStr sender, ubot::Encoding::ConstStr inviter, void* async_0, void* async_1));
	void __stdcall UNativeStr_WithSuffix(ubotAppSetOnMemberLeftHandler)(void* ctx, void* user, EventResultType(__stdcall* handler)(void* ctx, void* user, ubot::Encoding::ConstStr bot, ubot::Encoding::ConstStr source, ubot::Encoding::ConstStr sender));
	void __stdcall UNativeStr_WithSuffix(ubotAppSetOnMemberLeftAsyncHandler)(void* ctx, void* user, EventResultType(__stdcall* handler)(void* ctx, void* user, ubot::Encoding::ConstStr bot, ubot::Encoding::ConstStr source, ubot::Encoding::ConstStr sender, void* async_0, void* async_1));
	void __stdcall UNativeStr_WithSuffix(ubotAppSetProcessGroupInvitationHandler)(void* ctx, void* user, EventResultType(__stdcall* handler)(void* ctx, void* user, ubot::Encoding::ConstStr bot, ubot::Encoding::ConstStr sender, ubot::Encoding::ConstStr target, ubot::Encoding::ConstStr reason, void* respondedReason));
	void __stdcall UNativeStr_WithSuffix(ubotAppSetProcessGroupInvitationAsyncHandler)(void* ctx, void* user, EventResultType(__stdcall* handler)(void* ctx, void* user, ubot::Encoding::ConstStr bot, ubot::Encoding::ConstStr sender, ubot::Encoding::ConstStr target, ubot::Encoding::ConstStr reason, void* async_0, void* async_1));
	void __stdcall UNativeStr_WithSuffix(ubotAppSetProcessFriendRequestHandler)(void* ctx, void* user, EventResultType(__stdcall* handler)(void* ctx, void* user, ubot::Encoding::ConstStr bot, ubot::Encoding::ConstStr sender, ubot::Encoding::ConstStr reason, void* respondedReason));
	void __stdcall UNativeStr_WithSuffix(ubotAppSetProcessFriendRequestAsyncHandler)(void* ctx, void* user, EventResultType(__stdcall* handler)(void* ctx, void* user, ubot::Encoding::ConstStr bot, ubot::Encoding::ConstStr sender, ubot::Encoding::ConstStr reason, void* async_0, void* async_1));
	void __stdcall UNativeStr_WithSuffix(ubotAppSetProcessMembershipRequestHandler)(void* ctx, void* user, EventResultType(__stdcall* handler)(void* ctx, void* user, ubot::Encoding::ConstStr bot, ubot::Encoding::ConstStr source, ubot::Encoding::ConstStr sender, ubot::Encoding::ConstStr inviter, ubot::Encoding::ConstStr reason, void* respondedReason));
	void __stdcall UNativeStr_WithSuffix(ubotAppSetProcessMembershipRequestAsyncHandler)(void* ctx, void* user, EventResultType(__stdcall* handler)(void* ctx, void* user, ubot::Encoding::ConstStr bot, ubot::Encoding::ConstStr source, ubot::Encoding::ConstStr sender, ubot::Encoding::ConstStr inviter, ubot::Encoding::ConstStr reason, void* async_0, void* async_1));
	void __stdcall UNativeStr_WithSuffix(ubotAppHost)(void* ctx, ubot::Encoding::ConstStr op, ubot::Encoding::ConstStr urlStr, ubot::Encoding::ConstStr id);
	ubot::Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetGroupName)(void* ctx, ubot::Encoding::ConstStr bot, ubot::Encoding::ConstStr id);
	void __stdcall UNativeStr_WithSuffix(ubotAppGetGroupNameAsync)(void* ctx, void* user, ubot::Encoding::ConstStr bot, ubot::Encoding::ConstStr id, void(__stdcall* handler)(void* ctx, void* user, ubot::Encoding::ConstStr result));
	ubot::Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetUserName)(void* ctx, ubot::Encoding::ConstStr bot, ubot::Encoding::ConstStr id);
	void __stdcall UNativeStr_WithSuffix(ubotAppGetUserNameAsync)(void* ctx, void* user, ubot::Encoding::ConstStr bot, ubot::Encoding::ConstStr id, void(__stdcall* handler)(void* ctx, void* user, ubot::Encoding::ConstStr result));
	void __stdcall UNativeStr_WithSuffix(ubotAppSendChatMessage)(void* ctx, ubot::Encoding::ConstStr bot, ChatMessageType type, ubot::Encoding::ConstStr source, ubot::Encoding::ConstStr target, ubot::Encoding::ConstStr message);
	void __stdcall UNativeStr_WithSuffix(ubotAppSendChatMessageAsync)(void* ctx, void* user, ubot::Encoding::ConstStr bot, ChatMessageType type, ubot::Encoding::ConstStr source, ubot::Encoding::ConstStr target, ubot::Encoding::ConstStr message, void(__stdcall* handler)(void* ctx, void* user));
	void __stdcall UNativeStr_WithSuffix(ubotAppRemoveMember)(void* ctx, ubot::Encoding::ConstStr bot, ubot::Encoding::ConstStr source, ubot::Encoding::ConstStr target);
	void __stdcall UNativeStr_WithSuffix(ubotAppRemoveMemberAsync)(void* ctx, void* user, ubot::Encoding::ConstStr bot, ubot::Encoding::ConstStr source, ubot::Encoding::ConstStr target, void(__stdcall* handler)(void* ctx, void* user));
	void __stdcall UNativeStr_WithSuffix(ubotAppShutupMember)(void* ctx, ubot::Encoding::ConstStr bot, ubot::Encoding::ConstStr source, ubot::Encoding::ConstStr target, int duration);
	void __stdcall UNativeStr_WithSuffix(ubotAppShutupMemberAsync)(void* ctx, void* user, ubot::Encoding::ConstStr bot, ubot::Encoding::ConstStr source, ubot::Encoding::ConstStr target, int duration, void(__stdcall* handler)(void* ctx, void* user));
	void __stdcall UNativeStr_WithSuffix(ubotAppShutupAllMember)(void* ctx, ubot::Encoding::ConstStr bot, ubot::Encoding::ConstStr source, bool shutupSwitch);
	void __stdcall UNativeStr_WithSuffix(ubotAppShutupAllMemberAsync)(void* ctx, void* user, ubot::Encoding::ConstStr bot, ubot::Encoding::ConstStr source, bool shutupSwitch, void(__stdcall* handler)(void* ctx, void* user));
	ubot::Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetMemberName)(void* ctx, ubot::Encoding::ConstStr bot, ubot::Encoding::ConstStr source, ubot::Encoding::ConstStr target);
	void __stdcall UNativeStr_WithSuffix(ubotAppGetMemberNameAsync)(void* ctx, void* user, ubot::Encoding::ConstStr bot, ubot::Encoding::ConstStr source, ubot::Encoding::ConstStr target, void(__stdcall* handler)(void* ctx, void* user, ubot::Encoding::ConstStr result));
	ubot::Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetUserAvatar)(void* ctx, ubot::Encoding::ConstStr bot, ubot::Encoding::ConstStr id);
	void __stdcall UNativeStr_WithSuffix(ubotAppGetUserAvatarAsync)(void* ctx, void* user, ubot::Encoding::ConstStr bot, ubot::Encoding::ConstStr id, void(__stdcall* handler)(void* ctx, void* user, ubot::Encoding::ConstStr result));
	ubot::Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetSelfID)(void* ctx, ubot::Encoding::ConstStr bot);
	void __stdcall UNativeStr_WithSuffix(ubotAppGetSelfIDAsync)(void* ctx, void* user, ubot::Encoding::ConstStr bot, void(__stdcall* handler)(void* ctx, void* user, ubot::Encoding::ConstStr result));
	ubot::Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetPlatformID)(void* ctx, ubot::Encoding::ConstStr bot);
	void __stdcall UNativeStr_WithSuffix(ubotAppGetPlatformIDAsync)(void* ctx, void* user, ubot::Encoding::ConstStr bot, void(__stdcall* handler)(void* ctx, void* user, ubot::Encoding::ConstStr result));
	ubot::Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetGroupList)(void* ctx, ubot::Encoding::ConstStr bot);
	void __stdcall UNativeStr_WithSuffix(ubotAppGetGroupListAsync)(void* ctx, void* user, ubot::Encoding::ConstStr bot, void(__stdcall* handler)(void* ctx, void* user, ubot::Encoding::ConstStr result));
	ubot::Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotAppGetMemberList)(void* ctx, ubot::Encoding::ConstStr bot, ubot::Encoding::ConstStr id);
	void __stdcall UNativeStr_WithSuffix(ubotAppGetMemberListAsync)(void* ctx, void* user, ubot::Encoding::ConstStr bot, ubot::Encoding::ConstStr id, void(__stdcall* handler)(void* ctx, void* user, ubot::Encoding::ConstStr result));
}

inline auto& ubotAppSetOnReceiveChatMessageHandler = UNativeStr_WithSuffix(ubotAppSetOnReceiveChatMessageHandler);
inline auto& ubotAppSetOnReceiveChatMessageAsyncHandler = UNativeStr_WithSuffix(ubotAppSetOnReceiveChatMessageAsyncHandler);
inline auto& ubotAppSetOnMemberJoinedHandler = UNativeStr_WithSuffix(ubotAppSetOnMemberJoinedHandler);
inline auto& ubotAppSetOnMemberJoinedAsyncHandler = UNativeStr_WithSuffix(ubotAppSetOnMemberJoinedAsyncHandler);
inline auto& ubotAppSetOnMemberLeftHandler = UNativeStr_WithSuffix(ubotAppSetOnMemberLeftHandler);
inline auto& ubotAppSetOnMemberLeftAsyncHandler = UNativeStr_WithSuffix(ubotAppSetOnMemberLeftAsyncHandler);
inline auto& ubotAppSetProcessGroupInvitationHandler = UNativeStr_WithSuffix(ubotAppSetProcessGroupInvitationHandler);
inline auto& ubotAppSetProcessGroupInvitationAsyncHandler = UNativeStr_WithSuffix(ubotAppSetProcessGroupInvitationAsyncHandler);
inline auto& ubotAppSetProcessFriendRequestHandler = UNativeStr_WithSuffix(ubotAppSetProcessFriendRequestHandler);
inline auto& ubotAppSetProcessFriendRequestAsyncHandler = UNativeStr_WithSuffix(ubotAppSetProcessFriendRequestAsyncHandler);
inline auto& ubotAppSetProcessMembershipRequestHandler = UNativeStr_WithSuffix(ubotAppSetProcessMembershipRequestHandler);
inline auto& ubotAppSetProcessMembershipRequestAsyncHandler = UNativeStr_WithSuffix(ubotAppSetProcessMembershipRequestAsyncHandler);
inline auto& ubotAppHost = UNativeStr_WithSuffix(ubotAppHost);
inline auto& ubotAppGetGroupName = UNativeStr_WithSuffix(ubotAppGetGroupName);
inline auto& ubotAppGetGroupNameAsync = UNativeStr_WithSuffix(ubotAppGetGroupNameAsync);
inline auto& ubotAppGetUserName = UNativeStr_WithSuffix(ubotAppGetUserName);
inline auto& ubotAppGetUserNameAsync = UNativeStr_WithSuffix(ubotAppGetUserNameAsync);
inline auto& ubotAppSendChatMessage = UNativeStr_WithSuffix(ubotAppSendChatMessage);
inline auto& ubotAppSendChatMessageAsync = UNativeStr_WithSuffix(ubotAppSendChatMessageAsync);
inline auto& ubotAppRemoveMember = UNativeStr_WithSuffix(ubotAppRemoveMember);
inline auto& ubotAppRemoveMemberAsync = UNativeStr_WithSuffix(ubotAppRemoveMemberAsync);
inline auto& ubotAppShutupMember = UNativeStr_WithSuffix(ubotAppShutupMember);
inline auto& ubotAppShutupMemberAsync = UNativeStr_WithSuffix(ubotAppShutupMemberAsync);
inline auto& ubotAppShutupAllMember = UNativeStr_WithSuffix(ubotAppShutupAllMember);
inline auto& ubotAppShutupAllMemberAsync = UNativeStr_WithSuffix(ubotAppShutupAllMemberAsync);
inline auto& ubotAppGetMemberName = UNativeStr_WithSuffix(ubotAppGetMemberName);
inline auto& ubotAppGetMemberNameAsync = UNativeStr_WithSuffix(ubotAppGetMemberNameAsync);
inline auto& ubotAppGetUserAvatar = UNativeStr_WithSuffix(ubotAppGetUserAvatar);
inline auto& ubotAppGetUserAvatarAsync = UNativeStr_WithSuffix(ubotAppGetUserAvatarAsync);
inline auto& ubotAppGetSelfID = UNativeStr_WithSuffix(ubotAppGetSelfID);
inline auto& ubotAppGetSelfIDAsync = UNativeStr_WithSuffix(ubotAppGetSelfIDAsync);
inline auto& ubotAppGetPlatformID = UNativeStr_WithSuffix(ubotAppGetPlatformID);
inline auto& ubotAppGetPlatformIDAsync = UNativeStr_WithSuffix(ubotAppGetPlatformIDAsync);
inline auto& ubotAppGetGroupList = UNativeStr_WithSuffix(ubotAppGetGroupList);
inline auto& ubotAppGetGroupListAsync = UNativeStr_WithSuffix(ubotAppGetGroupListAsync);
inline auto& ubotAppGetMemberList = UNativeStr_WithSuffix(ubotAppGetMemberList);
inline auto& ubotAppGetMemberListAsync = UNativeStr_WithSuffix(ubotAppGetMemberListAsync);