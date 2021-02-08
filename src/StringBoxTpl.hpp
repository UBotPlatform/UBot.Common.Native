#include "UNativeStrHelper.h"
#include "StringBox.h"
using namespace ubot;

void __stdcall UNativeStr_WithSuffix(ubotStringBoxSet)(void* x, Encoding::ConstStr str)
{
	auto box = static_cast<std::string*>(x);
	*box = EncodingImpl::TempFrom(str).get();
}

Encoding::ConstStr __stdcall UNativeStr_WithSuffix(ubotStringBoxGet)(void* x)
{
	auto box = static_cast<std::string*>(x);
	if constexpr (std::is_same_v<Encoding, UTF8Encoding>)
	{
		return box->c_str();
	}
	else
	{
		thread_local static auto data = EncodingImpl::PermTo(box->c_str());
		return data.get();
	}
}