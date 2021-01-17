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
	struct WindowsAnsiEncodingImpl : WindowsAnsiEncoding
	{
		struct TempFrom
		{
		private:
			std::unique_ptr<char[]> data;
		public:
			TempFrom(ConstStr x)
				: data(ConvertBetweenMBCS(x, ::ubot::ActiveCodePage, 65001))
			{
			}
			const char* get() const noexcept
			{
				return this->data.get();
			}
		};
		struct PermTo
		{
		private:
			std::unique_ptr<char[]> data;
		public:
			PermTo(const char* x)
				: data(ConvertBetweenMBCS(x, 65001, ::ubot::ActiveCodePage))
			{
			}
			ConstStr get() const noexcept
			{
				return this->data.get();
			}
		};
		using TempTo = PermTo;
	};
#endif
	struct WideStringEncodingImpl : WideStringEncoding
	{
		struct TempFrom
		{
		private:
			std::string data;
		public:
			TempFrom(ConstStr x)
				: data(std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(x))
			{
			}
			const char* get() const noexcept
			{
				return this->data.c_str();
			}
		};
		struct PermTo
		{
		private:
			std::wstring data;
		public:
			PermTo(const char* x)
				: data(std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(x))
			{
			}
			ConstStr get() const noexcept
			{
				return this->data.c_str();
			}
		};
		using TempTo = PermTo;
	};
	struct UTF8EncodingImpl : UTF8Encoding
	{
		struct TempFrom
		{
		private:
			const char* data;
		public:
			TempFrom(ConstStr x)
				: data(x)
			{
			}
			const char* get() const noexcept
			{
				return data;
			}
		};
		struct PermTo
		{
		private:
			std::unique_ptr<char[]> data;
		public:
			PermTo(const char* x)
			{
				if (x == nullptr)
				{
					data = nullptr;
					return;
				}
				auto len = strlen(x);
				data = std::make_unique<char[]>(len + 1);
				memcpy(data.get(), x, len + 1);
			}
			ConstStr get() const noexcept
			{
				return this->data.get();
			}
		};
		struct TempTo
		{
		private:
			const char* data;
		public:
			TempTo(const char* x)
				: data(x)
			{
			}
			ConstStr get() const noexcept
			{
				return data;
			}
		};
	};
#if defined(UNativeStr_WindowsAnsi)
	using EncodingImpl = WindowsAnsiEncodingImpl;
#elif defined(UNativeStr_WideString)
	using EncodingImpl = WideStringEncodingImpl;
#elif defined(UNativeStr_UTF8)
	using EncodingImpl = UTF8EncodingImpl;
#endif
}