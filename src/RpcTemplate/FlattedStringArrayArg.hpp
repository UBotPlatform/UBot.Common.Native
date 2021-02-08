#pragma once
#include "JsonRpc.h"
#include "UNativeStrHelper.h"
namespace ubot
{
	template<char Separator = '|'>
	struct FlattedStringArrayArg
	{
		using NativeType = EncodingImpl::ConstStr;
		static void Write(TWriter& writer, EncodingImpl::ConstStr x)
		{
			auto data = EncodingImpl::TempFrom(x);
			const char* start = data.get();
			const char* cur = start;
			writer.StartArray();
			while (*cur != '\0')
			{
				if (*cur == Separator)
				{
					writer.String(start, cur - start);
					start = cur + 1;
				}
				cur++;
			}
			if (cur - start != 0)
			{
				writer.String(start, cur - start);
			}
			writer.EndArray();
		}
		static EncodingImpl::PermTo TempRead(const rapidjson::Value* x)
		{
			return PempRead(x);
		}
		static EncodingImpl::PermTo PempRead(const rapidjson::Value* x)
		{
			std::string r;
			if (!x || !x->IsArray()) 
			{
				return EncodingImpl::PermTo(nullptr);
			}
			auto iter = x->Begin();
			auto end = x->End();
			if (iter != end) 
			{
				if (!iter->IsString())
				{
					r.append("<error>");
				}
				else
				{
					r.append(iter->GetString(), iter->GetStringLength());
				}
				iter++;
			}
			for (; iter != end; ++iter)
			{
				r.push_back(Separator);
				if (!iter->IsString())
				{
					r.append("<error>");
				}
				else
				{
					r.append(iter->GetString(), iter->GetStringLength());
				}
			}
			return EncodingImpl::PermTo(r.c_str());
		}
	};
}