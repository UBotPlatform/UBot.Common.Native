#pragma once
#if !(defined(UNativeStr_WindowsAnsi) || defined(UNativeStr_WideString) || defined(UNativeStr_UTF8))
#if defined(_UNICODE)
#pragma message "UBot: Encoding not specified, use WideString by default because _UNICODE detected"
#define UNativeStr_WideString
#elif defined(_WIN32)
#pragma message "UBot: Encoding not specified, use WindowsAnsi by default because _UNICODE is not detected but you are using Windows"
#define UNativeStr_WindowsAnsi
#else
#pragma message "UBot: Encoding not specified, use UTF-8 by default because _UNICODE and _WIN32 is not detected"
#define UNativeStr_UTF8
#endif
#endif
#if defined(UNativeStr_WindowsAnsi)
#define UNativeStr_WithSuffix(name) name##A
typedef char UNativeChar;
#elif defined(UNativeStr_WideString)
#define UNativeStr_WithSuffix(name) name##W
typedef wchar_t UNativeChar;
#elif defined(UNativeStr_UTF8)
#define UNativeStr_WithSuffix(name) name##U8
typedef char UNativeChar;
#endif
typedef const UNativeChar* UNativeStr;
inline const constexpr int UNativeBufferSize = 1024;