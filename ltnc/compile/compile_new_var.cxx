#include "compile.hxx"
namespace ltn::c {

	StmtCode compile_new_variable(const ast::NewVar & new_var, CompilerInfo & info, Scope & scope) {
		const auto var = scope.insert(new_var.name, new_var.location);
		InstructionBuffer buf;
		if(new_var.expression) {
			buf << compile_expression(*new_var.expression, info, scope).code;
		}
		else {
			buf << ltn::inst::Null{};
		}
		buf << ltn::inst::Writex{var.address};
		return { buf, 0, true };
	}
}