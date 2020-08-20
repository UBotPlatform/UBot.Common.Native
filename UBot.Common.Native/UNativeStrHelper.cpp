#include <memory>
#ifdef _WIN32
#include <Windows.h>
#endif

#ifdef _WIN32
namespace ubot
{
    std::unique_ptr<char[]> ConvertBetweenMBCS(const char* x, int sourceCP, int targetCP)
    {
        if (x == nullptr)
        {
            return nullptr;
        }
        size_t rawLen = strlen(x) + 1;
        int dwUnicodeLen = MultiByteToWideChar(sourceCP, 0, x, (DWORD)rawLen, nullptr, 0);
        auto unicode = std::make_unique<wchar_t[]>(dwUnicodeLen);
        MultiByteToWideChar(sourceCP, 0, x, (DWORD)rawLen, unicode.get(), dwUnicodeLen);

        int len = WideCharToMultiByte(targetCP, 0, unicode.get(), dwUnicodeLen, nullptr, 0, nullptr, nullptr);
        auto result = std::make_unique<char[]>(len);;
        WideCharToMultiByte(targetCP, 0, unicode.get(), dwUnicodeLen, result.get(), len, nullptr, nullptr);
        return result;
    }
}
#endif