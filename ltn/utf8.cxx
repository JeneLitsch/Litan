#include "utf8.hxx"
#include <stdexcept>

namespace ltn::utf8 {
	std::uint32_t last_bits(std::uint8_t data, std::uint32_t n) {
		const std::uint32_t shift = 8 - n;
		return ((static_cast<std::uint32_t>(data) << shift) & 0xff) >> shift;
	}



	std::uint32_t first_bits(std::uint8_t data, std::uint32_t n) {
		const std::uint32_t shift = 8 - n;
		return (static_cast<std::uint32_t>(data) >> shift) & 0xff;
	}



	std::size_t predict_char_size(std::string_view str) {
		const std::uint8_t chr = static_cast<std::uint8_t>(str[0]);
		if(chr == '\0') return 0;
		if(first_bits(chr, 1) == 0) return 1;
		if(first_bits(chr, 3) == 0b110) return 2;
		if(first_bits(chr, 4) == 0b1110) return 3;
		if(first_bits(chr, 5) == 0b11110) return 4;
		throw std::runtime_error{"Invalid UTF-8"};
	}



	std::tuple<std::uint32_t, std::size_t> decode_char(std::string_view str) {
		const std::size_t size_in_bytes = predict_char_size(str);
		if(size_in_bytes > str.size()) {
			throw std::runtime_error{"Invalid UTF-8"};
		}
		switch (size_in_bytes) {
			case 0: {
				return {0,0};
			}
			case 1: {
				return { str[0], size_in_bytes };
			}
			case 2: {
				const std::uint32_t code 
					= (last_bits(static_cast<std::uint8_t>(str[0]), 5) << 6)
					| (last_bits(static_cast<std::uint8_t>(str[1]), 6) << 0);
				return { code, size_in_bytes };
			}
			case 3: {
				const std::uint32_t code 
					= (last_bits(static_cast<std::uint8_t>(str[0]), 4) << 12)
					| (last_bits(static_cast<std::uint8_t>(str[1]), 6) << 6)
					| (last_bits(static_cast<std::uint8_t>(str[2]), 6) << 0);
				return { code, size_in_bytes };
			}
			case 4: {
				const std::uint32_t code 
					= (last_bits(static_cast<std::uint8_t>(str[0]), 3) << 18)
					| (last_bits(static_cast<std::uint8_t>(str[1]), 6) << 12)
					| (last_bits(static_cast<std::uint8_t>(str[2]), 6) << 6)
					| (last_bits(static_cast<std::uint8_t>(str[3]), 6) << 0);
				return { code, size_in_bytes };
			}
			default: {
				throw std::runtime_error{"Invalid UTF-8"};
			}
		}
	}



	std::string encode_char(std::uint32_t code) {
		if(code >= 0x0000 && code <= 0x007F) {
			const std::array<char, 1> data {
				static_cast<char>(code),
			};
			return std::string { std::begin(data), std::end(data) };
		}
		if(code >= 0x0080 && code <= 0x07FF) {
			const std::array<char, 2> data {
				static_cast<char>(0b1100'0000 | last_bits(static_cast<std::uint8_t>(code >> 6), 5)),
				static_cast<char>(0b1000'0000 | last_bits(static_cast<std::uint8_t>(code >> 0), 6)),
			};
			return std::string { std::begin(data), std::end(data) };
		}
		if(code >= 0x0800 && code <= 0xFFFF) {
			const std::array<char, 3> data {
				static_cast<char>(0b1110'0000 | last_bits(static_cast<std::uint8_t>(code >> 12), 5)),
				static_cast<char>(0b1000'0000 | last_bits(static_cast<std::uint8_t>(code >> 6), 6)),
				static_cast<char>(0b1000'0000 | last_bits(static_cast<std::uint8_t>(code >> 0), 6)),
			};
			return std::string { std::begin(data), std::end(data) };
		}
		if(code >= 0x10000 && code <= 0x10FFFF) {
			const std::array<char, 4> data {
				static_cast<char>(0b1111'0000 | last_bits(static_cast<std::uint8_t>(code >> 18), 5)),
				static_cast<char>(0b1000'0000 | last_bits(static_cast<std::uint8_t>(code >> 12), 6)),
				static_cast<char>(0b1000'0000 | last_bits(static_cast<std::uint8_t>(code >> 6), 6)),
				static_cast<char>(0b1000'0000 | last_bits(static_cast<std::uint8_t>(code >> 0), 6)),
			};
			return std::string { std::begin(data), std::end(data) };
		}
		return "";
	}



	std::vector<std::uint32_t> decode_string(std::string_view string) {
		std::string_view rest = string;
		std::vector<std::uint32_t> codes;
		while(!rest.empty()) {
			auto [code, stride] = decode_char(rest);
			if(stride) {
				codes.push_back(code);
				rest.remove_prefix(stride);
			}
			else {
				break;
			}
		}
		return codes;
	}



	std::string encode_string(std::span<const std::uint32_t> codes) {
		std::string string;
		for(std::uint32_t code : codes) {
			string.append(encode_char(code));
		}
		return string;
	}



	std::string_view character_at(std::string_view string, std::size_t index) {
		for(std::int64_t i = 0; i < static_cast<std::int64_t>(index); i++) {
			const std::size_t stride = predict_char_size(string);
			if(stride == 0) {
				throw std::out_of_range{ "UTF-8 out of range" };
			}
			string.remove_prefix(stride);
		}
		return string.substr(0, predict_char_size(string));
	}



	std::uint32_t code_point_at(std::string_view string, std::size_t index) {
		auto [code, stride] = decode_char(character_at(string, index));
		return code;
	}



	std::size_t character_count(std::string_view string) {
		std::size_t count = 0;
		while(!string.empty()) {
			const std::size_t stride = predict_char_size(string);
			string.remove_prefix(stride);
			count++;
		}
		return count;
	}
}