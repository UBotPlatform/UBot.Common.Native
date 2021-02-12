#include "RpcTemplate/ApiDefiner.hpp"
UBotPP_ApiCall_T(GetGroupName, ubot::StringArg, "get_group_name", (ubot::StringArg, bot), (ubot::StringArg, id));
UBotPP_ApiCall_T(GetUserName, ubot::StringArg, "get_user_name", (ubot::StringArg, bot), (ubot::StringArg, id));
UBotPP_ApiCall_T(SendChatMessage, ubot::VoidArg, "send_chat_message", (ubot::StringArg, bot), (ubot::EnumArg<ChatMessageType>, type), (ubot::StringArg, source), (ubot::StringArg, target), (ubot::StringArg, message));
UBotPP_ApiCall_T(RemoveMember, ubot::VoidArg, "remove_member", (ubot::StringArg, bot), (ubot::StringArg, source), (ubot::StringArg, target));
UBotPP_ApiCall_T(ShutupMember, ubot::VoidArg, "shutup_member", (ubot::StringArg, bot), (ubot::StringArg, source), (ubot::StringArg, target), (ubot::IntArg, duration));
UBotPP_ApiCall_T(ShutupAllMember, ubot::VoidArg, "shutup_all_member", (ubot::StringArg, bot), (ubot::StringArg, source), (ubot::BoolArg, shutupSwitch));
UBotPP_ApiCall_T(GetMemberName, ubot::StringArg, "get_member_name", (ubot::StringArg, bot), (ubot::StringArg, source), (ubot::StringArg, target));
UBotPP_ApiCall_T(GetUserAvatar, ubot::StringArg, "get_user_avatar", (ubot::StringArg, bot), (ubot::StringArg, id));
UBotPP_ApiCall_T(GetSelfID, ubot::StringArg, "get_self_id", (ubot::StringArg, bot));
UBotPP_ApiCall_T(GetPlatformID, ubot::StringArg, "get_platform_id", (ubot::StringArg, bot));
UBotPP_ApiCall_T(GetGroupList, ubot::FlattedStringArrayArg<>, "get_group_list", (ubot::StringArg, bot));
UBotPP_ApiCall_T(GetMemberList, ubot::FlattedStringArrayArg<>, "get_member_list", (ubot::StringArg, bot), (ubot::StringArg, id));
UBotPP_HandlerSetter_T(OnReceiveChatMessage, ubot::NormalEventResultArg, "on_receive_chat_message", (ubot::StringArg, bot), (ubot::EnumArg<ChatMessageType>, type), (ubot::StringArg, source), (ubot::StringArg, sender), (ubot::StringArg, message), (ubot::JsonRawArg, info));
UBotPP_HandlerSetter_T(OnMemberJoined, ubot::NormalEventResultArg, "on_member_joined", (ubot::StringArg, bot), (ubot::StringArg, source), (ubot::StringArg, sender), (ubot::StringArg, inviter));
UBotPP_HandlerSetter_T(OnMemberLeft, ubot::NormalEventResultArg, "on_member_left", (ubot::StringArg, bot), (ubot::StringArg, source), (ubot::StringArg, sender));
UBotPP_HandlerSetter_T(ProcessGroupInvitation, ubot::ReasonableEventResponder, "process_group_invitation", (ubot::StringArg, bot), (ubot::StringArg, sender), (ubot::StringArg, target), (ubot::StringArg, reason));
UBotPP_HandlerSetter_T(ProcessFriendRequest, ubot::ReasonableEventResponder, "process_friend_request", (ubot::StringArg, bot), (ubot::StringArg, sender), (ubot::StringArg, reason));
UBotPP_HandlerSetter_T(ProcessMembershipRequest, ubot::ReasonableEventResponder, "process_membership_request", (ubot::StringArg, bot), (ubot::StringArg, source), (ubot::StringArg, sender), (ubot::StringArg, inviter), (ubot::StringArg, reason));