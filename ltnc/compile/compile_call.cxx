#include "compile.hxx"
#include "stdxx/functional.hxx"
#include <string_view>
#include "conversion.hxx"

namespace ltn::c {
	// compiles function call fx(...)
	InstructionBuffer compile_expr(const sst::Invoke & invoke, CompilerInfo & info, Scope & scope) {
			InstructionBuffer buf;

			buf << compile_expression(*invoke.function_ptr, info, scope);

			for(const auto & param : invoke.parameters) {
				buf << compile_expression(*param, info, scope);
			}

			buf << inst::newarr(invoke.parameters.size());
			buf << inst::invoke();

			return buf;
	}



	InstructionBuffer compile_expr(const sst::Call & call, CompilerInfo & info, Scope & scope) {
			InstructionBuffer buf;
			for(std::size_t i = 0; i < call.parameters.size(); ++i) {
				buf << compile_expression(*call.parameters[i], info, scope);
			}
			buf << inst::call(call.id);		
			return buf;
	}
}