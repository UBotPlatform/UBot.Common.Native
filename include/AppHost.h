#pragma once
#include "EventResultType.h"
#include "ChatMessageType.h"
#include "UNativeStr.h"
#include "RpcTemplate/RpcHelperMacro.hpp"

#define UBotPP_ApiCall_T(funcName, TResult, name, ...)\
	extern "C"\
	{\
		UBotPP_DefineApiCallSync(UNativeStr_WithSuffix(ubotApp ## funcName), TResult, name, __VA_ARGS__);\
		UBotPP_DefineApiCallAsync(UNativeStr_WithSuffix(ubotApp ## funcName ## Async), TResult, name, __VA_ARGS__);\
	}\
	inline auto& ubotApp ## funcName = UNativeStr_WithSuffix(ubotApp ## funcName);\
	inline auto& ubotApp ## funcName ## Async = UNativeStr_WithSuffix(ubotApp ## funcName ## Async)

#define UBotPP_HandlerSetter_T(funcName, TResult, name, ...)\
	extern "C"\
	{\
		UBotPP_DefineSyncHandlerSetter(UNativeStr_WithSuffix(ubotAppSet ## funcName ## Handler), TResult, name, __VA_ARGS__);\
		UBotPP_DefineAsyncHandlerSetter(UNativeStr_WithSuffix(ubotAppSet ## funcName ## AsyncHandler), TResult, name, __VA_ARGS__);\
	}\
	inline auto& ubotAppSet ## funcName ## Handler = UNativeStr_WithSuffix(ubotAppSet ## funcName ## Handler);\
	inline auto& ubotAppSet ## funcName ## AsyncHandler = UNativeStr_WithSuffix(ubotAppSet ## funcName ## AsyncHandler)
#include "AppApiDefiner.hpp"
#undef UBotPP_ApiCall_T
#undef UBotPP_HandlerSetter_T

extern "C"
{
	void* __stdcall ubotAppNew();
	void __stdcall ubotAppDelete(void* ctx);
	void __stdcall UNativeStr_WithSuffix(ubotAppHost)(void* ctx, ubot::Encoding::ConstStr op, ubot::Encoding::ConstStr urlStr, ubot::Encoding::ConstStr id);
}
inline auto& ubotAppHost = UNativeStr_WithSuffix(ubotAppHost);
