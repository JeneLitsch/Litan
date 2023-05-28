#include "analyze.hxx"
#include <iostream>
#include "conversion.hxx"

namespace ltn::c {
	void guard_const(const ast::Node & node, const Scope & scope) {
		if(scope.is_const()) {
			throw const_assign_violation(node);
		}
	}



	namespace {
		sst::bind_ptr generate_binding(sst::expr_ptr l) {
			if(auto * l_local = as<sst::Var>(*l)) {
				return std::make_unique<sst::LocalBinding>(
					l_local->address
				);
			}
			if(auto * l_index = as<sst::Index>(*l)) {
				return std::make_unique<sst::IndexBinding>(
					std::move(l_index->expr),
					std::move(l_index->index)
				);
			}
			if(auto * l_member = as<sst::Member>(*l)) {
				return std::make_unique<sst::MemberBinding>(
					std::move(l_member->expr),
					l_member->address
				);
			}
			if(auto * l_global = as<sst::GlobalVar>(*l)) {
				return std::make_unique<sst::GlobalBinding>(
					l_global->address
				);
			}
			if(auto * l_ref = as<sst::Deref>(*l)) {
				return std::make_unique<sst::RefBinding>(
					std::move(l_ref->expr)
				);
			}
			return nullptr;
		}
	}



	sst::stmt_ptr analyze_stmt(const ast::Assign & stmt, Scope & scope) {
		guard_const(stmt, scope);
		auto l = analyze_expression(*stmt.l, scope);
		auto r = analyze_expression(*stmt.r, scope);
		auto binding = generate_binding(std::move(l));
		if(!binding) {
			throw left_side_not_assignable(stmt);
		}
		return std::make_unique<sst::Assign>(std::move(binding), std::move(r));
	}
}