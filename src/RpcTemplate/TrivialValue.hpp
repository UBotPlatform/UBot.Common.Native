#pragma once
#include<functional>
namespace ubot
{
	template<typename T>
	struct TrivialValue
	{
	private:
		T data;
	public:
		TrivialValue(T x)
			: data(x)
		{
		}
		T get() const noexcept
		{
			return data;
		}
	};

	template <typename T>
	struct is_trivial_value : std::bool_constant<false>
	{
	};
	template <typename TValue>
	struct is_trivial_value<TrivialValue<TValue>> : std::bool_constant<true>
	{
	};
	template<class T> inline constexpr bool is_trivial_value_v = is_trivial_value<T>::value;
}
