#pragma once
#if !(defined(UNativeStr_WindowsAnsi) || defined(UNativeStr_WideString) || defined(UNativeStr_UTF8))
#if defined(_UNICODE)
#pragma message ("UBot: Encoding not specified, use WideString by default because _UNICODE detected")
#define UNativeStr_WideString
#elif defined(_WIN32)
#pragma message ("UBot: Encoding not specified, use WindowsAnsi by default because _UNICODE is not detected but you are using Windows")
#define UNativeStr_WindowsAnsi
#else
#pragma message ("UBot: Encoding not specified, use UTF-8 by default because _UNICODE and _WIN32 is not detected")
#define UNativeStr_UTF8
#endif
#endif
namespace ubot
{
#ifdef _WIN32
    struct WindowsAnsiEncoding {
        using Char = char;
        using Str = char*;
        using ConstStr = const char*;
    };
#endif
    struct UTF8Encoding {
        using Char = char;
        using Str = char*;
        using ConstStr = const char*;
    };
    struct WideStringEncoding {
        using Char = wchar_t;
        using Str = wchar_t*;
        using ConstStr = const wchar_t*;
    };
#if defined(UNativeStr_WindowsAnsi)
    using Encoding = WindowsAnsiEncoding;
#elif defined(UNativeStr_WideString)
    using Encoding = WideStringEncoding;
#elif defined(UNativeStr_UTF8)
    using Encoding = UTF8Encoding;
#endif
}
#if defined(UNativeStr_WindowsAnsi)
#define UNativeStr_WithSuffix(name) name##A
#elif defined(UNativeStr_WideString)
#define UNativeStr_WithSuffix(name) name##W
#elif defined(UNativeStr_UTF8)
#define UNativeStr_WithSuffix(name) name##U8
#endif
inline const constexpr int UNativeBufferSize = 1024;