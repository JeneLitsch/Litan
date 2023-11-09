#include "analyze.hxx"
#include <iostream>
#include "stdxx/iife.hxx"
#include "ltn/MemberCode.hxx"
#include "ltnc/sst/expr/Map.hxx"
#include "ltnc/sst/expr/Struct.hxx"

namespace ltn::c {
	namespace {
		sst::expr::Struct::Member analyze_member(Context &, sst::expr_ptr expr, MemberCode code) {
			return sst::expr::Struct::Member {
				.address = static_cast<std::uint8_t>(code),
				.expr = std::move(expr),
			};
		}


		
		sst::expr::Struct::Member analyze_member(Context & context, sst::expr_ptr expr, const std::string & name) {
			return sst::expr::Struct::Member {
				.address = context.member_table.get_id(name),
				.expr = std::move(expr),
			};
		}
	}


	sst::expr_ptr analyze_expr(const ast::Struct & init, Scope & scope) {
		
		auto sst_init = sst::expr::strukt();

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


	
	sst::expr_ptr analyze_expr(const ast::Map & init, Scope & scope) {
		auto map = sst::expr::map();
		for(auto & [key, val] : init.pairs) {
			map->pairs.push_back(sst::expr::Map::Pair{
				.key = analyze_expression(*key, scope),
				.val = analyze_expression(*val, scope),
			});
		}
		return map;
	}
}