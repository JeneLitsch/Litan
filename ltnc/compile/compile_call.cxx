#include "compile.hxx"
#include <string_view>
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
			call.parameters.size());
		
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

		for(const auto & param : call.parameters) {
			buf << compile_expression(*param, info, scope).code;
		}

		buf << ltn::inst::Call{fx->id};
		
		return ExprCode{ buf };
	}
}