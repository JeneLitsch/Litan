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
			{"shift_l", Inst::SHIFT_L},
			{"shift_r", Inst::SHIFT_R},

			{"neg", Inst::NEG},
			{"not", Inst::NOT},
			{"inc", Inst::INC},
			{"dec", Inst::DEC},

			{"newu", Inst::NEWU},
			{"newi", Inst::NEWI},
			{"newf", Inst::NEWF},
			{"newfx", Inst::NEWFX},
			{"newclock", Inst::NEWCLOCK},
			{"true", Inst::TRUE},
			{"false", Inst::FALSE},
			{"newarr", Inst::NEWARR},
			{"newstr", Inst::NEWSTR},
			{"newout_std", Inst::NEWOUT_STD},
			{"newin_std", Inst::NEWIN_STD},
			{"null", Inst::NVLL},
			{"char", Inst::CHAR},
			{"elem", Inst::ELEM},

			{"jump", Inst::JUMP},
			{"call", Inst::CALL},
			{"return", Inst::RETURN},
			{"ifelse", Inst::IF},
			{"error", Inst::ERROR},
			{"exit", Inst::EXIT},
			{"invoke", Inst::INVOKE},
			{"external", Inst::EXTERNAL},

			{"read", Inst::READ},
			{"write", Inst::WRITE},
			{"scrap", Inst::SCRAP},
			{"makevar", Inst::MAKEVAR},
			{"at", Inst::AT},
			{"at_write", Inst::AT_WRITE},
			{"read_x", Inst::READ_X},
			{"write_x", Inst::WRITE_X},
			{"read_0", Inst::READ_0},
			{"read_1", Inst::READ_1},
			{"read_2", Inst::READ_2},
			{"read_3", Inst::READ_3},
			{"write_0", Inst::WRITE_0},
			{"write_1", Inst::WRITE_1},
			{"write_2", Inst::WRITE_2},
			{"write_3", Inst::WRITE_3},
			
			{"out", Inst::OUT},
			{"in_str", Inst::IN_STR},
			{"in_line", Inst::IN_LINE},
			{"in_int", Inst::IN_INT},
			{"in_float", Inst::IN_FLOAT},

			{"min", Inst::MIN},
			{"max", Inst::MAX},
			{"round", Inst::ROUND},
			{"floor", Inst::FLOOR},
			{"ceil", Inst::CEIL},
			{"abs", Inst::ABS},
			{"hypot", Inst::HYPOT},
			{"sqrt", Inst::SQRT},
			
			{"sin", Inst::SIN},
			{"cos", Inst::COS},
			{"tan", Inst::TAN},

			{"size", Inst::SIZE},
			{"front", Inst::FRONT},
			{"back", Inst::BACK},

			{"to_seconds", Inst::TO_SECONDS},
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