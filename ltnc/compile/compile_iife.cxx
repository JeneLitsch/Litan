#include "compile.hxx"
#include <string_view>
namespace ltn::c {
	ExprResult compile_iife(const ast::Iife & iife, CompilerInfo & info, Scope & outer_scope) {
		const auto jumpmark = make_jump_id("IIFE");
		MinorScope inner_scope{&outer_scope};
		inner_scope.override_return_type(iife.return_type);
		inner_scope.set_return(jumpmark);
		InstructionBuffer buf;
		buf << compile_statement(*iife.stmt, info, inner_scope).code;
		buf << inst::null();
		buf << inst::label(jumpmark);
		return { 
			.code = buf,
			.deduced_type = iife.return_type,
		};
	}
}