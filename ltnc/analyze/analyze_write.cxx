#include "analyze.hxx"
#include "ltnc/type/check.hxx"
#include <iostream>
#include "conversion.hxx"

namespace ltn::c {
	void guard_const(const ast::Node & node, const Scope & scope) {
		if(scope.is_const()) {
			throw CompilerError{
				"Cannot modify or reassign variable in const function",
				node.location};
		}
	}



	sst::stmt_ptr analyze_stmt(
		const ast::Assign & expr,
		Context & context,
		Scope & scope) {
		guard_const(expr, scope);
		auto l = analyze_expression(*expr.l, context, scope);
		auto r = conversion_on_assign(analyze_expression(*expr.r, context, scope), l->type, expr.location);
		if(auto * l_local = dynamic_cast<sst::Var *>(l.get())) {
			return std::make_unique<sst::AssignLocal>(
				0, false,
				l_local->addr,
				std::move(r)
			);
		}
		if(auto * l_index = dynamic_cast<sst::Index *>(l.get())) {
			return std::make_unique<sst::AssignIndex>(
				0, false,
				std::move(l_index->expression),
				std::move(l_index->index),
				std::move(r)
			);
		}
		if(auto * l_member = dynamic_cast<sst::Member *>(l.get())) {
			return std::make_unique<sst::AssignMember>(
				0, false,
				std::move(l_member->expr),
				l_member->addr,
				std::move(r)
			);
		}
		if(auto * l_global = dynamic_cast<sst::GlobalVar *>(l.get())) {
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