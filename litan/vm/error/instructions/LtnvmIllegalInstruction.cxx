#include "LtnvmIllegalInstruction.hxx"

ltn::vm::IllegalInstruction::IllegalInstruction(std::uint8_t opcode)
	: RuntimeError("Illegal Instruction: " + std::to_string(opcode)), opcode(opcode) {}

std::uint8_t ltn::vm::IllegalInstruction::getOpCode() const {
	return this->opcode;
}