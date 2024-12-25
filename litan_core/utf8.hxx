#pragma once
#include <cstdint>
#include <span>
#include <vector>
#include <string_view>
#include <string>


namespace ltn::utf8 {
	std::tuple<std::uint32_t, std::size_t> decode_char(std::string_view str);
	std::vector<std::uint32_t> decode_string(std::string_view string);
	
	std::string encode_char(std::uint32_t code);
	std::string encode_string(std::span<const std::uint32_t> codes);
	
	std::string_view character_at(std::string_view string, std::size_t index);
	std::uint32_t code_point_at(std::string_view string, std::size_t index);

	std::size_t character_count(std::string_view string);
}