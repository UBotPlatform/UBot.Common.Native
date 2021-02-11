#pragma once
namespace ubot
{
	template<typename T>
	struct EnumArg
	{
		using NativeType = T;
		using EnumType = T;
	};
}