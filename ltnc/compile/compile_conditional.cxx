#include "compile.hxx"
#include <sstream>
namespace ltn::c {
	namespace {
		std::string jump_else(const std::string & id) {
			return id + "_ELSE";
		}

		std::string jump_end(const std::string & id) {
			return id + "_END";
		}
	}



	InstructionBuffer compile_conditional(
		const std::string & name,
		const InstructionBuffer & condition,
		const InstructionBuffer & if_branch,
		const InstructionBuffer * else_branch) {

		if(else_branch) {
			const auto to_else = jump_else(name); 
			const auto to_end = jump_end(name);
			
			InstructionBuffer buf;
			buf << condition;
			buf << inst::ifelse(to_else);

			buf << if_branch;
			buf << inst::jump(to_end);

			buf << inst::label(to_else);
			buf << *else_branch;

			buf << inst::label(to_end);

			return buf;
		}

		else {
			const auto to_else = jump_else(name); 

			InstructionBuffer buf;
			
			buf << condition;
			buf << inst::ifelse(to_else);

			buf << if_branch;
			buf << inst::label(to_else);

			return buf;
		}
	}
}