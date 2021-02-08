#pragma once
enum class EventResultType
{
	Ignore = 0,
	Continue = 1,
	Complete = 2,
	AcceptRequest = 10,
	RejectRequest = 20
};