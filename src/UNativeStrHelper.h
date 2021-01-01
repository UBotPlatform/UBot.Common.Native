#pragma once
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include "UNativeStr.h"
#include <memory>
#include <string>
#include <codecvt>
#include <locale>
#include <vector>
namespace ubot
{
#ifdef _WIN32
    extern int ActiveCodePage;
    std::unique_ptr<char[]> ConvertBetweenMBCS(const char* x, int sourceCP, int targetCP);
    struct WindowsAnsiEncodingImpl : WindowsAnsiEncoding {
        static std::unique_ptr<char[]> TempFrom_S(ConstStr x) {
            return ConvertBetweenMBCS(x, ::ubot::ActiveCodePage, 65001);
        }
        static const char* TempFrom_G(const std::unique_ptr<char[]>& x) {
            return x.get();
        }
        static std::unique_ptr<char[]> PermTo_S(ConstStr x) {
            return ConvertBetweenMBCS(x, ::ubot::ActiveCodePage, 65001);
        }
        static const char* PermTo_G(const std::unique_ptr<char[]>& x) {
            return x.get();
        }
        static std::unique_ptr<char[]> TempTo_S(const char* x) {
            return PermTo_S(x);
        }
        static const char* TempTo_G(const std::unique_ptr<char[]>& x) {
            return PermTo_G(x);
        }
    };
#endif
    struct WideStringEncodingImpl : WideStringEncoding {
        static std::string TempFrom_S(ConstStr x) {
            return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(x);
        }
        static const char* TempFrom_G(const std::string& x) {
            return x.c_str();
        }
        static std::wstring PermTo_S(const char* x) {
            return std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(x);
        }
        static const wchar_t* PermTo_G(const std::wstring& x) {
            return x.c_str();
        }
        static std::wstring TempTo_S(const char* x) {
            return PermTo_S(x);
        }
        static const wchar_t* TempTo_G(const std::wstring& x) {
            return PermTo_G(x);
        }
    };
    struct UTF8EncodingImpl : UTF8Encoding {
        static const char* TempFrom_S(ConstStr x) {
            return x;
        }
        static const char* TempFrom_G(const char* x) {
            return x;
        }
        static std::unique_ptr<char[]> PermTo_S(ConstStr x) {
            if (x == nullptr)
            {
                return nullptr;
            }
            auto len = strlen(x);
            auto result = std::make_unique<char[]>(len + 1);
            memcpy(result.get(), x, len + 1);
            return result;
        }
        static const char* PermTo_G(const std::unique_ptr<char[]>& x) {
            return x.get();
        }
        static const char* TempTo_S(ConstStr x) {
            return x;
        }
        static const char* TempTo_G(const char* x) {
            return x;
        }
    };
#if defined(UNativeStr_WindowsAnsi)
    using EncodingImpl = WindowsAnsiEncodingImpl;
#elif defined(UNativeStr_WideString)
    using EncodingImpl = WideStringEncodingImpl;
#elif defined(UNativeStr_UTF8)
    using EncodingImpl = UTF8EncodingImpl;
#endif
}