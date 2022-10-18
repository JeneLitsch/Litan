#include "compile.hxx"
#include "ltnc/type/check.hxx"

namespace ltn::c {
	namespace {
		ExprCode compile_new_variable_right(
			const ast::NewVar & new_var,
			CompilerInfo & info,
			Scope & scope) {
			
			if(new_var.expression) {
				return compile_expression(*new_var.expression, info, scope);
			}
			else {
				InstructionBuffer buf;
				buf << ltn::inst::Null{};
				return ExprCode {
					.code = buf,
					.deduced_type = type::Null{}, 
				};
			}
		}

	}


	StmtCode compile_new_variable(const ast::NewVar & new_var, CompilerInfo & info, Scope & scope) {
		const auto var = scope.insert(new_var.name, new_var.location, new_var.type);
		const auto r = compile_new_variable_right(new_var, info, scope);
		
		if(type::is_convertible(r.deduced_type, new_var.type)) {
			InstructionBuffer buf;
			buf << r.code;
			buf << ltn::inst::Writex{var.address};
			return { 
				.code = buf,
				.var_count = 0,
				.direct_allocation = true,
			};
		}
		else throw cannot_assign(r.deduced_type, var.type);
	}
}