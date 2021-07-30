#pragma once
#include "LtnError.hxx"
namespace ltn {
	class IllegalInstruction : Error {
	public:
		IllegalInstruction(std::uint8_t opcode);
		std::uint8_t getOpCode() const;
	private:
		std::uint8_t opcode;
	};
}