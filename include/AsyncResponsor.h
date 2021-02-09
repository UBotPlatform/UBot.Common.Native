#pragma once
#include "EventResultType.h"
#include "UNativeStr.h"
extern "C"
{
	void __stdcall ubotAsyncReturnNormalEventResult(void* async, EventResultType type);
	void __stdcall UNativeStr_WithSuffix(ubotAsyncReturnReasonableEventResult)(void* async, EventResultType type, ubot::Encoding::ConstStr reason);
}
inline auto& ubotAsyncReturnReasonableEventResult = UNativeStr_WithSuffix(ubotAsyncReturnReasonableEventResult);