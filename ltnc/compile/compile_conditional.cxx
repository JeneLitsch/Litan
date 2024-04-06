#include "compile.hxx"
#include <sstream>
#include "ltnc/sst/expr/Conditional.hxx"
#include "ltnc/sst/stmt/Conditional.hxx"

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



	namespace {
		InstructionBuffer compile_conditional_cascade(const auto & sst, const auto & compile_body) {
			InstructionBuffer buf;
			const auto id = make_jump_id("CONDTIONAL");
			const auto label_end = id + "_END";
			const auto label_case = [&] (auto i) {
				return id + "_" + std::to_string(i + 1);
			};

			std::uint64_t i = 0;
			for(; i < std::size(sst.cases); ++i) {
				auto & [c,b] = sst.cases[i];
				buf << inst::label(label_case(i));
				buf << compile_expression(*c);
				buf << inst::ifelse(label_case(i + 1));
				buf << compile_body(*b);
				buf << inst::jump(label_end);
			}
			buf << inst::label(label_case(i));
			if(sst.else_branch) {
				buf << compile_body(*sst.else_branch);
			}
			buf << inst::label(label_end);
			return buf;
		}
	}



	InstructionBuffer compile_expr(const sst::expr::Conditional & sst) {
		return compile_conditional_cascade(sst, compile_expression);
	}


	
	InstructionBuffer compile_stmt(const sst::stmt::Conditional & sst) {
		return compile_conditional_cascade(sst, compile_statement);
	}
}