#include "LtnaNumberParser.hxx"

std::uint32_t ltn::a::toInt32(const std::string & str) {
	return static_cast<std::uint32_t>(toInt64(str));
}

std::uint8_t ltn::a::toInt8(const std::string & str) {
	return static_cast<std::uint8_t>(toInt64(str));
}


std::uint64_t ltn::a::toInt64(const std::string & str) {
	if(str.substr(0,2) == "0x"){
		return static_cast<std::uint64_t>(std::stoull(str.substr(2), nullptr, 16));
	}
	if(str.substr(0,2) == "0b"){
		return static_cast<std::uint64_t>(std::stoull(str.substr(2), nullptr, 2));
	}
	return static_cast<std::uint64_t>(std::stoull(str, nullptr, 10));
}