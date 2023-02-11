#include "analyze.hxx"

namespace ltn::c {
	sst::expr_ptr analyze_expr(
		const ast::InitStruct & init,
		Context & context,
		Scope & scope) {
		
		auto sst_init = std::make_unique<sst::InitStruct>();

		for(const auto & [member, expr] : init.members) {
			sst_init->members.push_back(sst::InitStruct::Member {
				.addr = context.member_table.get_id(member),
				.expr = analyze_expression(*expr, context, scope)
			});
		}

		return sst_init;
	}
}