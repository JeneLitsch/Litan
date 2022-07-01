#include "compile.hxx"
#include <string_view>
namespace ltn::c {
	ExprCode compile_iife(const ast::Iife & iife, CompilerInfo & info, Scope & outer_scope) {
		const auto jumpmark = make_jump_id("IIFE");
		Scope inner_scope{&outer_scope};
		inner_scope.set_return(jumpmark);
		InstructionBuffer buf;
		buf << compile_statement(*iife.stmt, info, inner_scope).code;
		buf << ltn::inst::Null{};
		buf << ltn::inst::Label{jumpmark};
		return { buf };
	}
}