#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include "LtnInstructions.hxx"
#include "LtnHeapTypes.hxx"
#include "LtnIoFormat.hxx"

namespace ltna {
	// command format
	std::uint64_t cFormat(InstCode opcode);
	// functioncode format
	std::uint64_t fFormat(InstCode opcode, std::uint8_t funct);
	std::uint64_t fFormat(InstCode opcode, ltn::HeapType type);
	std::uint64_t fFormat(InstCode opcode, ltn::OuputFormat format);
	// value format with 32bit parameter
	std::uint64_t vFormat(InstCode opcode, std::uint32_t val);
	// jump format with 56bit parameter
	std::uint64_t jFormat(InstCode opcode, std::uint64_t dest);
	
	std::uint64_t dFormat(InstCode opcode, std::uint64_t arg56);
	std::uint64_t dFormat(const std::vector<std::string> & stringData);
}