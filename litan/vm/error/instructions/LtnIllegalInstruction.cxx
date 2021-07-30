#include "LtnIllegalInstruction.hxx"

ltn::IllegalInstruction::IllegalInstruction(std::uint8_t opcode)
	: Error("Illegal Instruction: " + std::to_string(opcode)), opcode(opcode) {}

std::uint8_t ltn::IllegalInstruction::getOpCode() const {
	return this->opcode;
}