#pragma once
namespace ubot
{
	template<typename TArg>
	struct NormalResultResponder
	{
		using NativeType = typename TArg::NativeType;
		using NativeTypeEx = void;
	};
}