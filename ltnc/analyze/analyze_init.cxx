#include "analyze.hxx"

namespace ltn::c {
	sst::expr_ptr analyze_expr(const ast::InitStruct & init, Scope & scope) {
		
		auto sst_init = std::make_unique<sst::InitStruct>();

		auto & context = scope.get_context();

		for(const auto & [member, expr] : init.members) {
			sst_init->members.push_back(sst::InitStruct::Member {
				.address = context.member_table.get_id(member),
				.expr = analyze_expression(*expr, scope),
			});
		}

		return sst_init;
	}
}