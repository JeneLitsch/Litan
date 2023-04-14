#include "compile.hxx"
#include "stdxx/functional.hxx"
#include <string_view>

namespace ltn::c {
	// compiles function call fx(...)
	InstructionBuffer compile_expr(const sst::Invoke & invoke) {
		InstructionBuffer buf;

		buf << compile_expression(*invoke.function_ptr);

		for(const auto & arg : invoke.arguments) {
			buf << compile_expression(*arg);
		}

		buf << inst::newarr(invoke.arity());
		buf << inst::invoke();

		return buf;
	}



	InstructionBuffer compile_expr(const sst::Call & call) {
		InstructionBuffer buf;

		for(const auto & argument : call.arguments) {
			buf << compile_expression(*argument);
		}

		buf << inst::call(call.label.to_string(), static_cast<std::uint8_t>(call.arity()));		
		return buf;
	}



	InstructionBuffer compile_expr(const sst::InvokeMember & invoke) {
		InstructionBuffer buf;

		buf << compile_expression(*invoke.object);
		buf << inst::duplicate();
		buf << inst::member_read(invoke.member_id);
		buf << inst::swap();
		
		for(const auto & arg : invoke.arguments) {
			buf << compile_expression(*arg);
		}

		buf << inst::newarr(invoke.arity());
		buf << inst::invoke();

		return buf;
	}
}