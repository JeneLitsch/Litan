#include "analyze.hxx"
#include "ltnc/type/traits.hxx"
#include <iostream>
#include "conversion.hxx"

namespace ltn::c {
	void guard_const(const ast::Node & node, const Scope & scope) {
		if(scope.is_const()) {
			throw CompilerError{
				"Cannot modify or reassign variable in const function",
				node.location
			};
		}
	}



	sst::stmt_ptr analyze_stmt(
		const ast::Assign & expr,
		Context & context,
		Scope & scope) {
		guard_const(expr, scope);
		auto l = analyze_expression(*expr.l, context, scope);
		auto r_raw = analyze_expression(*expr.r, context, scope);
		auto r = conversion_on_assign(std::move(r_raw), l->type, expr.location);
		if(auto * l_local = as<sst::Var>(*l)) {
			return std::make_unique<sst::AssignLocal>(
				0, false,
				l_local->addr,
				std::move(r)
			);
		}
		if(auto * l_index = as<sst::Index>(*l)) {
			return std::make_unique<sst::AssignIndex>(
				0, false,
				std::move(l_index->expression),
				std::move(l_index->index),
				std::move(r)
			);
		}
		if(auto * l_member = as<sst::Member>(*l)) {
			return std::make_unique<sst::AssignMember>(
				0, false,
				std::move(l_member->expr),
				l_member->addr,
				std::move(r)
			);
		}
		if(auto * l_global = as<sst::GlobalVar>(*l)) {
			return std::make_unique<sst::AssignGlobal>(
				0, false,
				l_global->addr,
				std::move(r)
			);
		}
		throw CompilerError {
			"Left side is not assignable",
			expr.location
		};
	}
}