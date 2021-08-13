#include "LtnaInstructionBuilder.hxx"
#include "LtnaStringDecoder.hxx"
#include <iostream>
#include "LtnaNumberParser.hxx"
#include "LtnaStringDataTooLong.hxx"

std::uint64_t ltn::a::cInst(InstCode opcode) {
	return static_cast<std::uint8_t>(opcode);
}

std::uint64_t ltn::a::fInstFunct(InstCode opcode, std::uint8_t funct) {
	return static_cast<std::uint8_t>(opcode)
		| static_cast<std::uint64_t>(funct) << 8;
}

std::uint64_t ltn::a::fInstType(InstCode opcode, ltn::HeapType type) {
	return fInstFunct(opcode, static_cast<std::uint8_t>(type));
}

std::uint64_t ltn::a::fInstFormat(InstCode opcode, ltn::OuputFormat format) {
	return fInstFunct(opcode, static_cast<std::uint8_t>(format));
}

std::uint64_t ltn::a::vInst(InstCode opcode, std::uint32_t val) {
	return static_cast<std::uint8_t>(opcode)
		| static_cast<std::uint64_t>(val) << 32;
}

std::uint64_t ltn::a::jInst(InstCode opcode, std::uint64_t dest) {
	return static_cast<std::uint8_t>(opcode)
		| static_cast<std::uint64_t>(dest) << 8;
}

std::uint64_t ltn::a::xInst(InstCode opcode, const std::vector<std::string> & charData) {
	if(charData.size() > 6) {
		throw StringDataTooLong();
	}
	std::uint64_t inst = 0;
	inst |= static_cast<std::uint64_t>(opcode);
	inst |= static_cast<std::uint64_t>(charData.size()) << 8;
	
	for(std::size_t i = 0; i < charData.size(); i++) {
		std::uint8_t chr = toInt8(charData[i]);
		inst |= static_cast<std::uint64_t>(chr) << (i+2)*8;
	}

	return inst;
}

std::uint64_t ltn::a::pInst(InstCode opcode, std::uint8_t flags, std::uint32_t value) {
	return static_cast<std::uint8_t>(opcode)
		| static_cast<std::uint64_t>(flags) << 8
		| static_cast<std::uint64_t>(value) << 32;
}