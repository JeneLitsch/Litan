#include "compile.hxx"
namespace ltn::c {

	StmtCode compile_new_variable(const ast::NewVar & new_var, CompilerInfo & info, Scope & scope) {
		using VQ = Variable::Qualifier;
		const auto qualifier = new_var.is_const ? VQ::CONST : VQ::MUTABLE;
		const auto var = scope.insert(
			new_var.name, qualifier, new_var.location);
		InstructionBuffer buf;
		if(new_var.expression) {
			const auto expr = compile_expression(*new_var.expression, info, scope);
			buf << expr.code;
		}
		else {
			buf << ltn::inst::Null{};
		}
		buf << ltn::inst::Writex{var.address};
		return { buf, 0, true };
	}
}