#pragma once
#include <unordered_map>
namespace ubot
{
	namespace unordered_string_map_details
	{
		struct string_equal : public std::equal_to<>
		{
			using is_transparent = void;
		};

		struct string_hash 
		{
			using is_transparent = void;
			using key_equal = string_equal;
			using transparent_key_equal = string_equal;
			using hash_type = std::hash<std::string_view>;
			size_t operator()(std::string_view txt) const { return hash_type{}(txt); }
			size_t operator()(const std::string& txt) const { return hash_type{}(txt); }
			size_t operator()(const char* txt) const { return hash_type{}(txt); }
		};
	}
	template<typename TValue>
	using unordered_string_map = std::unordered_map<std::string, TValue, unordered_string_map_details::string_hash, unordered_string_map_details::string_equal>;
}