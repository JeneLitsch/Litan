#include "compile.hxx"
namespace ltn::c::compile {
	// compiles variable creation -> var foo ...;
	StmtCode new_variable_like(
		const auto & new_variable,
		CompilerInfo & info,
		Scope & scope,
		Variable::Qualifier qualifier) {
		
		const auto var = scope.insert(
			new_variable.name, qualifier, new_variable.location);
		std::stringstream ss;
		if(new_variable.expression) {
			const auto expr = compile::expression(*new_variable.expression, info, scope);
			ss << expr.code;
		}
		else {
			ss << inst::null;
		}
		ss << inst::write_x(var.address);
		return {ss.str(), 0, true};
	}
	


	StmtCode new_const(const ast::NewConst & stmt, CompilerInfo & info, Scope & scope) {
		return new_variable_like(stmt, info, scope, Variable::Qualifier::CONST);
	}
	


	StmtCode new_variable(const ast::NewVar & stmt, CompilerInfo & info, Scope & scope) {
		return new_variable_like(stmt, info, scope, Variable::Qualifier::MUTABLE);
	}
}