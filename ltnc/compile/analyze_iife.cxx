#include "compile.hxx"
#include <string_view>
namespace ltn::c {
	sst::expr_ptr analyze_expr(
		const ast::Iife & iife,
		CompilerInfo & info,
		Scope & outer_scope) {

		const auto return_label = make_jump_id("IIFE");
		MinorScope inner_scope{&outer_scope};
		const auto return_type = instantiate_type(iife.return_type, inner_scope);
		inner_scope.override_return_type(return_type);
		inner_scope.set_return(return_label);
		auto body = analyze_statement(*iife.stmt, info, inner_scope);


		return std::make_unique<sst::Iife>(
			return_type,
			return_label,
			std::move(body),
			return_type
		);
	}
}