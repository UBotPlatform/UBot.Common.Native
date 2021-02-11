#pragma once
#include "../../UNativeStr.h"
namespace ubot
{
	template<char Separator = '|'>
	struct FlattedStringArrayArg
	{
		using NativeType = Encoding::ConstStr;
	};
}