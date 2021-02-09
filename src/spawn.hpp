#pragma once
namespace ubot
{
	struct spawn_t 
	{
		struct promise_type 
		{
			spawn_t get_return_object() noexcept { return {}; }
			std::experimental::suspend_never initial_suspend() noexcept { return {}; }
			std::experimental::suspend_never final_suspend() noexcept { return {}; }
			void return_void() noexcept {}
			void unhandled_exception() noexcept {}
		};
	};
}