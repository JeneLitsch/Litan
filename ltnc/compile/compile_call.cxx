#include "compile.hxx"
#include "stdxx/functional.hxx"
#include <string_view>
#include "ltnc/sst/expr/Call.hxx"
#include "ltnc/sst/expr/Invoke.hxx"
#include "ltnc/sst/expr/InvokeMember.hxx"

namespace ltn::c {
	namespace {
		std::uint8_t get_arity_uint8(auto & node) {
			if(node.arity() > 255) throw CompilerError {
				"Function arity exceeds limit of 255"
			};
			return static_cast<std::uint8_t>(node.arity());
		}
	}


	// compiles function call fx(...)
	InstructionBuffer compile_expr(const sst::expr::Invoke & invoke) {
		InstructionBuffer buf;

		for(const auto & arg : invoke.arguments) {
			buf << compile_expression(*arg);
		}
		
		buf << compile_expression(*invoke.function_ptr);
		buf << inst::invoke(get_arity_uint8(invoke));

		return buf;
	}



	InstructionBuffer compile_expr(const sst::expr::Call & call) {
		InstructionBuffer buf;

		for(const auto & argument : call.arguments) {
			buf << compile_expression(*argument);
		}

		buf << inst::call(call.label.to_string(), get_arity_uint8(call));		
		return buf;
	}



	InstructionBuffer compile_expr(const sst::expr::InvokeMember & invoke) {
		InstructionBuffer buf;

		buf << compile_expression(*invoke.object);
		buf << inst::duplicate();
		buf << inst::member_read(invoke.member_id);
		
		for(const auto & arg : invoke.arguments) {
			buf << compile_expression(*arg);
			buf << inst::swap();
		}

		buf << inst::invoke(get_arity_uint8(invoke));

		return buf;
	}
}