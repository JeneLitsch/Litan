#include "assemble.hxx"
#include "ltn/InstructionSet.hxx"
#include "ltna/InstructionTable.hxx"
#include "unordered_map"
namespace ltn::a::assemble {
	namespace {
		std::optional<std::uint8_t> assembleLine(std::istream & in) {
			std::string inst;
			in >> inst;
			if(inst == "byte") {
				std::uint16_t byte;
				in >> std::hex >> byte;
				return static_cast<std::uint8_t>(byte);
			}
			if(instructionTable.contains(inst)) {
				const auto [opcode, _] = instructionTable.at(inst);
				return static_cast<std::uint8_t>(opcode);
			}
			return {};
		}
	}


	std::vector<std::uint8_t> assemble(std::istream & in) {
		std::vector<std::uint8_t> bytecode;
		while(!in.eof()) {
			if(auto byte = assembleLine(in)) {
				bytecode.push_back(*byte);
			}
		}
		return bytecode;
	}
}