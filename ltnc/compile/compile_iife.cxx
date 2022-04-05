#include "compile.hxx"
#include <string_view>
namespace ltn::c::compile {
	ExprCode iife(const ast::Iife & iife, CompilerInfo & info, Scope & outer_scope) {
		const auto jumpmark = make_jump_id("IIFE");
		Scope inner_scope{&outer_scope};
		inner_scope.set_return(jumpmark);
		std::ostringstream ss;
		ss << compile::statement(*iife.stmt, info, inner_scope).code;
		ss << inst::null;
		ss << inst::jumpmark(jumpmark);
		return {ss.str()};
	}
}