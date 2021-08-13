#pragma once
#include "LtnRuntimeError.hxx"
namespace ltn::vm {
	class IllegalInstruction : RuntimeError {
	public:
		IllegalInstruction(std::uint8_t opcode);
		std::uint8_t getOpCode() const;
	private:
		std::uint8_t opcode;
	};
}