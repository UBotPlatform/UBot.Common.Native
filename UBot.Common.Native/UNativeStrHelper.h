#pragma once
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include "UNativeStr.h"
#include <memory>
#include <string>
#include <codecvt>
#include <locale>
#include <vector>
#ifdef _WIN32
namespace ubot
{
    extern int ActiveCodePage;
	std::unique_ptr<char[]> ConvertBetweenMBCS(const char* x, int sourceCP, int targetCP);
}
#endif
#if defined(UNativeStr_WindowsAnsi)
#define FromNativeString(x) ::ubot::ConvertBetweenMBCS(x, ::ubot::ActiveCodePage, 65001).get()
#define ToNativeString(x) ::ubot::ConvertBetweenMBCS(x, 65001, ::ubot::ActiveCodePage).get()
#define ToPermanentNativeString(x) ::ubot::ConvertBetweenMBCS(x, 65001, ::ubot::ActiveCodePage)
#define GetPermanentNativeString(x) (x).get()
#elif defined(UNativeStr_WideString)
#define FromNativeString(x) std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(x).c_str()
#define ToNativeString(x) std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(x).c_str()
#define ToPermanentNativeString(x) std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(x)
#define GetPermanentNativeString(x) (x).c_str()
#elif defined(UNativeStr_UTF8)
#define FromNativeString(x) (x)
#define ToNativeString(x) (x)
inline std::unique_ptr<char[]> ToPermanentNativeString(const char* x)
{
    if (x == nullptr)
    {
        return nullptr;
    }
    auto len = strlen(x);
    auto result = std::make_unique<char[]>(len + 1);
    memcpy(result.get(), x, len + 1);
    return result;
}
#define GetPermanentNativeString(x) (x).get()
#endif