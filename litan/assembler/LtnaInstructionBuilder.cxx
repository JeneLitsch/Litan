#include "LtnaInstructionBuilder.hxx"
#include "LtnaStringDecoder.hxx"
#include <iostream>

std::uint64_t ltna::cFormat(InstCode opcode) {
	return static_cast<std::uint8_t>(opcode);
}

std::uint64_t ltna::fFormat(InstCode opcode, std::uint8_t funct) {
	return static_cast<std::uint8_t>(opcode)
		| static_cast<std::uint64_t>(funct) << 8;
}

std::uint64_t ltna::fFormat(InstCode opcode, ltn::HeapType type) {
	return fFormat(opcode, static_cast<std::uint8_t>(type));
}

std::uint64_t ltna::fFormat(InstCode opcode, ltn::OuputFormat format) {
	return fFormat(opcode, static_cast<std::uint8_t>(format));
}

std::uint64_t ltna::vFormat(InstCode opcode, std::uint32_t val) {
	return static_cast<std::uint8_t>(opcode)
		| static_cast<std::uint64_t>(val) << 32;
}

std::uint64_t ltna::jFormat(InstCode opcode, std::uint64_t dest) {
	return static_cast<std::uint8_t>(opcode)
		| static_cast<std::uint64_t>(dest) << 8;
}

std::uint64_t ltna::dFormat(InstCode opcode, std::uint64_t arg56) {
	return static_cast<std::uint64_t>(opcode)
		| static_cast<std::uint64_t>(arg56) << 8;
}

std::uint64_t ltna::dFormat(const std::vector<std::string> & stringData) {
	std::uint64_t data = 0;
	const std::string str = StringDecoder::decode(stringData);
	const std::size_t len = str.size();
	if(len > 6) {
		std::cout << ">> Warning: String data to long" << std::endl;
	}
	data |= std::uint8_t(len);
	for(std::size_t i = 0; i < len; i++) {
		const char chr = str[i];
		data |= std::uint64_t(chr) << (i+1)*8;
	}
	return dFormat(InstCode::STRING_DATA, data); 
}
