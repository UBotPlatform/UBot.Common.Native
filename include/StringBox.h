#pragma once
#include "UNativeStr.h"
extern "C"
{
    void* __stdcall ubotStringBoxNew();
    void __stdcall ubotStringBoxDelete(void* x);
    void __stdcall UNativeStr_WithSuffix(ubotStringBoxSet)(void* x, ubot::Encoding::ConstStr str);
    ubot::Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotStringBoxGet)(void* x);
}
inline auto& ubotStringBoxSet = UNativeStr_WithSuffix(ubotStringBoxSet);
inline auto& ubotStringBoxGet = UNativeStr_WithSuffix(ubotStringBoxGet);
