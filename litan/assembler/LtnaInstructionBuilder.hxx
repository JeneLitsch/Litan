#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include "LtnInstructions.hxx"
#include "LtnHeapTypes.hxx"
#include "LtnIoFormat.hxx"

namespace ltna {
	// command format
	std::uint64_t inst1(InstCode opcode);
	// functioncode format
	std::uint64_t inst2Funct(InstCode opcode, std::uint8_t funct);
	std::uint64_t inst2Type(InstCode opcode, ltn::HeapType type);
	std::uint64_t inst2Format(InstCode opcode, ltn::OuputFormat format);
	// value format with 32bit parameter
	std::uint64_t inst4(InstCode opcode, std::uint32_t val);
	// jump format with 56bit parameter
	std::uint64_t inst8(InstCode opcode, std::uint64_t dest);
	
	std::uint64_t instX(InstCode opcode, const std::vector<std::string> & stringData);
}