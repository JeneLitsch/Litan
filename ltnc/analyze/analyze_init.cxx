#include "analyze.hxx"
#include <iostream>
#include "stdxx/iife.hxx"
#include "ltn/MemberCode.hxx"

namespace ltn::c {
	namespace {
		sst::InitStruct::Member analyze_member(Context &, sst::expr_ptr expr, MemberCode code) {
			return sst::InitStruct::Member {
				.address = static_cast<std::uint8_t>(code),
				.expr = std::move(expr),
			};
		}


		
		sst::InitStruct::Member analyze_member(Context & context, sst::expr_ptr expr, const std::string & name) {
			return sst::InitStruct::Member {
				.address = context.member_table.get_id(name),
				.expr = std::move(expr),
			};
		}
	}


	sst::expr_ptr analyze_expr(const ast::InitStruct & init, Scope & scope) {
		
		auto sst_init = std::make_unique<sst::InitStruct>();

		auto & context = scope.get_context();

		for(const auto & [member, expr] : init.members) {
			auto sst_expr = analyze_expression(*expr, scope);
			auto visitor = [&] (const auto & m) {
				return analyze_member(context, std::move(sst_expr), m);
			};
			sst_init->members.push_back(std::visit(visitor, member));
		}

		return sst_init;
	}
}