#include "compile.hxx"
#include <string_view>
#include "conversion.hxx"

namespace ltn::c {
	CompilerError undefined_function(
		const std::string_view & name,
		const ast::Node & node) {
		std::stringstream ss;
		ss << "Function " << name << " is not defined";
		return CompilerError { ss.str(), node.location };
	}



	// compiles function call fx(...)
	ExprCode compile_call(const ast::Call & call, CompilerInfo & info, Scope & scope) {
		const auto fx = info.fx_table.resolve(
			call.name,
			scope.get_namespace(),
			call.namespaze,
			call.arguments.size());
		
		if(!fx) {
			throw undefined_function(call.name, call);
		}

		guard_private(*fx, scope.get_namespace(), call.location);
		
		if(scope.is_const() && !fx->c0nst) {
			throw CompilerError {
				"Cannot call non-const function from a const functions",
				call.location};
		}

		InstructionBuffer buf;

		for(std::size_t i = 0; i < call.arguments.size(); ++i) {
			auto & arg_expr = call.arguments[i];
			auto & parameter = fx->parameters[i];
			auto arg = compile_expression(*arg_expr, info, scope);

			buf << arg.code;
			buf << conversion_on_pass(arg.deduced_type, parameter.type, { call.location, i });
		}

		buf << ltn::inst::Call{fx->id};
		
		return ExprCode{
			.code = buf,
			.deduced_type = fx->return_type,
		};
	}
}