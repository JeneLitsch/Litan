#include "assemble.hxx"
#include "ltn/InstructionSet.hxx"
#include "unordered_map"
namespace ltn::a::assemble {
	namespace {
		const static std::unordered_map<std::string_view, Inst> instTabel {
			{"add", Inst::ADD},
			{"sub", Inst::SUB},
			{"mlt", Inst::MLT},
			{"div", Inst::DIV},
			{"mod", Inst::MOD},
			{"eql", Inst::EQL},
			{"ueql", Inst::UEQL},
			{"sml", Inst::SML},
			{"bgr", Inst::BGR},
			{"smleql", Inst::SMLEQL},
			{"bgreql", Inst::BGREQL},

			{"neg", Inst::NEG},
			{"not", Inst::NOT},
			{"inc", Inst::INC},
			{"dec", Inst::DEC},

			{"newu", Inst::NEWU},
			{"newi", Inst::NEWI},
			{"newf", Inst::NEWF},
			{"addr", Inst::ADDR},
			{"true", Inst::TRUE},
			{"false", Inst::FALSE},
			{"newarr", Inst::NEWARR},
			{"null", Inst::NVLL},
			{"char", Inst::CHAR},

			{"jump", Inst::JUMP},
			{"call", Inst::CALL},
			{"return", Inst::RETURN},
			{"ifelse", Inst::IF},
			{"error", Inst::ERROR},
			{"exit", Inst::EXIT},

			{"read", Inst::READ},
			{"write", Inst::WRITE},
			{"scrap", Inst::SCRAP},
			{"makevar", Inst::MAKEVAR},
			
			{"out", Inst::OUT},

			{"alloc_str", Inst::ALLOC_STR},
			{"alloc_arr", Inst::ALLOC_ARR},
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
		return bytecode;
	}
}