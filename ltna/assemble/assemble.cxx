#include "assemble.hxx"
#include "ltn/InstructionSet.hxx"
#include "unordered_map"
namespace ltn::a::assemble {
	namespace {
		const static std::unordered_map<std::string_view, Inst> instTabel {
			{"addi", Inst::ADDI},
			{"subi", Inst::SUBI},
			{"mlti", Inst::MLTI},
			{"divi", Inst::DIVI},
			{"modi", Inst::MODI},
			{"eqli", Inst::EQLI},
			{"ueqli", Inst::UEQLI},
			{"smli", Inst::SMLI},
			{"bgri", Inst::BGRI},
			{"smleqli", Inst::SMLEQLI},
			{"bgreqli", Inst::BGREQLI},
			{"negi", Inst::NEGI},

			{"addf", Inst::ADDF},
			{"subf", Inst::SUBF},
			{"mltf", Inst::MLTF},
			{"divf", Inst::DIVF},
			{"modf", Inst::MODF},
			{"eqlf", Inst::EQLF},
			{"ueqlf", Inst::UEQLF},
			{"smlf", Inst::SMLF},
			{"bgrf", Inst::BGRF},
			{"smleqlf", Inst::SMLEQLF},
			{"bgreqlf", Inst::BGREQLF},
			{"negf", Inst::NEGF},

			{"newu", Inst::NEWU},
			{"newi", Inst::NEWI},
			{"newd", Inst::NEWF},
			{"true", Inst::TRUE},
			{"false", Inst::FALSE},
			{"read", Inst::READ},
			{"write", Inst::WRITE},
			{"scrap", Inst::SCRAP},

			{"jump", Inst::JUMP},
			{"link", Inst::LINK},
			{"return", Inst::RETURN},
			{"if", Inst::IF},
			{"error", Inst::ERROR},

			{"out", Inst::OUT},
		};


		std::uint8_t assembleLine(std::istream & in) {
			std::string inst;
			in >> inst;
			if(inst == "byte") {
				std::uint16_t byte;
				in >> std::hex >> byte;
				return static_cast<std::uint8_t>(byte);
			}
			if(instTabel.contains(inst)) {
				return static_cast<std::uint8_t>(instTabel.at(inst));
			}
			return 0;
		}
	}


	std::vector<std::uint8_t> assemble(std::istream & in) {
		std::vector<std::uint8_t> bytecode;
		while(!in.eof()) {
			bytecode.push_back(assembleLine(in));
		}
	}
}