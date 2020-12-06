#pragma once
#include <optional>
#include <mutex>
#include <condition_variable>
#include <rapidjson/document.h>
#include <chrono>
namespace ubot 
{
	template<typename TResult>
	class ResultBox
	{
	public:
		template<typename Rep, typename Period>
		std::optional<TResult> WaitForResult(const std::chrono::duration<Rep, Period>& relTime)
		{
			std::unique_lock <std::mutex> lck(mtx);
			if (!isCompletion)
			{
				completion.wait_for(lck, relTime);
				if (!isCompletion)
				{
					return std::nullopt;
				}
			}
			isCompletion = false;
			return std::optional<TResult>(std::move(result));
		}
		void SetResult(TResult&& r)
		{
			{
				std::unique_lock <std::mutex> lck(mtx);
				if (isCompletion) {
					throw std::exception("the result box has been set");
				}
				result = std::move(r);
				isCompletion = true;
			}
			completion.notify_one();
		}
		bool IsEmpty()
		{
			std::unique_lock <std::mutex> lck(mtx);
			return !isCompletion;
		}
	private:
		TResult result;
		bool isCompletion = false;
		std::condition_variable completion;
		std::mutex mtx;
	};
}