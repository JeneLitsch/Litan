#include "assemble.hxx"
#include "ltn/InstructionSet.hxx"
#include "ltna/InstructionTable.hxx"
#include "unordered_map"
namespace ltn::a::assemble {
	namespace {
		std::optional<std::uint8_t> assemble_line(std::istream & in) {
			std::string inst;
			in >> inst;
			if(inst == "byte") {
				std::uint16_t byte;
				in >> std::hex >> byte;
				return static_cast<std::uint8_t>(byte);
			}
			if(instruction_table.contains(inst)) {
				const auto opcode = instruction_table.at(inst).opcode;
				return static_cast<std::uint8_t>(opcode);
			}
			return {};
		}
	}


	std::vector<std::uint8_t> assemble(std::istream & in) {
		std::vector<std::uint8_t> bytecode;
		while(!in.eof()) {
			if(auto byte = assemble_line(in)) {
				bytecode.push_back(*byte);
			}
		}
		return bytecode;
	}
}