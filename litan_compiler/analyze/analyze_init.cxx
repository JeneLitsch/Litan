#include "analyze.hxx"
#include <iostream>
#include "stdxx/iife.hxx"

#include "litan_compiler/ast/expr/Map.hxx"
#include "litan_compiler/ast/expr/Struct.hxx"

#include "litan_compiler/sst/expr/Map.hxx"
#include "litan_compiler/sst/expr/Struct.hxx"

namespace ltn::c {

	sst::expr_ptr analyze_expr(const ast::expr::Struct & ast_struct, Scope & scope) {
		auto sst_struct = sst::expr::strukt();
		for(const auto & [name, expr] : ast_struct.members) {
			sst::expr_ptr sst_expr = analyze_expression(*expr, scope);
			const std::uint64_t address = scope.resolve_member_id(name);
			sst::expr::Struct::Member sst_member {
				.address = address,
				.expr = std::move(sst_expr),
			};
			sst_struct->members.push_back(std::move(sst_member));
		}

		return sst_struct;
	}


	
	sst::expr_ptr analyze_expr(const ast::expr::Map & ast_map, Scope & scope) {
		auto sst_map = sst::expr::map();
		for(auto & [key, val] : ast_map.pairs) {
			sst_map->pairs.push_back(sst::expr::Map::Pair{
				.key = analyze_expression(*key, scope),
				.val = analyze_expression(*val, scope),
			});
		}
		return sst_map;
	}
}