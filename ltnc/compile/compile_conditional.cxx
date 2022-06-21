#include "compile.hxx"
#include <sstream>
namespace ltn::c::compile {
	namespace {
		std::string jump_else(const std::string & id) {
			return id + "_ELSE";
		}

		std::string jump_end(const std::string & id) {
			return id + "_END";
		}
	}

	InstructionBuffer conditional(
		const std::string & name,
		const InstructionBuffer & condition,
		const InstructionBuffer & if_branch,
		const InstructionBuffer * else_branch) {

		if(else_branch) {
			const auto to_else = jump_else(name); 
			const auto to_end = jump_end(name);
			
			InstructionBuffer buf;
			buf << condition;
			buf << ltn::inst::Ifelse{to_else};

			buf << if_branch;
			buf << ltn::inst::Jump{to_end};

			buf << ltn::inst::Label{to_else};
			buf << *else_branch;

			buf << ltn::inst::Label{to_end};

			return buf;
		}

		else {
			const auto to_else = jump_else(name); 

			InstructionBuffer buf;
			
			buf << condition;
			buf << ltn::inst::Ifelse{to_else};

			buf << if_branch;
			buf << ltn::inst::Label{to_else};

			return buf;
		}
	}
}