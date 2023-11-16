#include "analyze.hxx"
#include <iostream>
#include "ltnc/sst/expr/Index.hxx"
#include "ltnc/sst/expr/Member.hxx"
#include "ltnc/sst/expr/Var.hxx"
#include "ltnc/sst/expr/GlobalVar.hxx"
#include "ltnc/sst/stmt/Assign.hxx"

namespace ltn::c {
	void guard_const(const ast::Node & node, const Scope & scope) {
		if(scope.is_const()) {
			throw const_assign_violation(node);
		}
	}



	sst::stmt_ptr analyze_stmt(const ast::stmt::Assign & stmt, Scope & scope) {
		guard_const(stmt, scope);
		auto l = analyze_expression(*stmt.l, scope);
		auto r = analyze_expression(*stmt.r, scope);
		auto binding = std::move(*l).convert_to_bindung();
		if(!binding) {
			throw left_side_not_assignable(stmt);
		}
		return sst::stmt::assign(std::move(binding), std::move(r));
	}
}