#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include "LtnInstructions.hxx"
#include "LtnHeapTypes.hxx"
#include "LtnIoFormat.hxx"

namespace ltna {
	// command format
	std::uint64_t cInst(InstCode opcode);
	
	// functioncode format
	std::uint64_t fInstFunct(InstCode opcode, std::uint8_t funct);
	std::uint64_t fInstType(InstCode opcode, ltn::HeapType type);
	std::uint64_t fInstFormat(InstCode opcode, ltn::OuputFormat format);
	
	// value format with 32bit parameter
	std::uint64_t vInst(InstCode opcode, std::uint32_t val);
		
	// jump format with 56bit parameter
	std::uint64_t jInst(InstCode opcode, std::uint64_t dest);
	
	std::uint64_t xInst(InstCode opcode, const std::vector<std::string> & charData);
	
	// paramterFormat
	std::uint64_t pInst(InstCode opcode, std::uint8_t flags, std::uint32_t value);
}