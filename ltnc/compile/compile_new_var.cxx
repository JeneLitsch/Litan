#include "compile.hxx"
namespace ltn::c::compile {

	StmtCode new_variable(const ast::NewVar & new_var, CompilerInfo & info, Scope & scope) {
		using VQ = Variable::Qualifier;
		const auto qualifier = new_var.is_const ? VQ::CONST : VQ::MUTABLE;
		const auto var = scope.insert(
			new_var.name, qualifier, new_var.location);
		std::stringstream ss;
		if(new_var.expression) {
			const auto expr = compile::expression(*new_var.expression, info, scope);
			ss << expr.code;
		}
		else {
			ss << inst::null;
		}
		ss << inst::write_x(var.address);
		return {ss.str(), 0, true};
	}
}