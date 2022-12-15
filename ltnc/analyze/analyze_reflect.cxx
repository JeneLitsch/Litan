#include "analyze.hxx"
#include <string_view>
#include <iostream>
namespace ltn::c {
	namespace {
		sst::Reflect::FunctionQuery fx_to_query(const ast::Functional & fx) {
			return sst::Reflect::FunctionQuery {
				.id        = fx.id,
				.name      = fx.name,
				.full_name = fx.namespaze.to_string() + fx.name,
				.arity     = fx.parameters.size(),
				.c0nst     = fx.c0nst,
				.pr1vate   = fx.pr1vate,
				.ext3rn    = fx.init,
			};
		}


		sst::Reflect::Addr make_member_addrs(MemberTable & member_table) {
			return sst::Reflect::Addr {
				.name      = member_table.get_id("name"),
				.full_name = member_table.get_id("full_name"),
				.fx_ptr    = member_table.get_id("fx_ptr"),
				.functions = member_table.get_id("functions"),
				.c0nst     = member_table.get_id("const"),
				.pr1vate   = member_table.get_id("private"),
				.ext3rn    = member_table.get_id("extern"),
			};
		}



		sst::Reflect::FunctionQuery analyze_reflect_query(
			const FunctionQuery & query,
			CompilerInfo & info) {

			const auto * fx = info.fx_table.resolve(
				query.name,
				query.namespaze,
				query.arity
			);

			if(!fx) {
				throw undefined_function(query.name, ast::Node{{}});
			}
			
			info.fx_queue.stage_function(*fx);
			return fx_to_query(*fx);
		}



		sst::Reflect::NamespaceQuery analyze_reflect_query(
			const NamespaceQuery & query,
			CompilerInfo & info) {

			sst::Reflect::NamespaceQuery sst_query;
			sst_query.namespaze = query.namespaze;
			for(const auto & fx : info.fx_table.get_symbols()) {
				if(fx->namespaze == query.namespaze) {
					info.fx_queue.stage_function(*fx);
					sst_query.functions.push_back(fx_to_query(*fx));
				}
			}
		
			return sst_query;
		}
	}



	// compiles array literal
	sst::expr_ptr analyze_expr(
		const ast::Reflect & refl,
		CompilerInfo & info,
		Scope &) {
			
		return std::make_unique<sst::Reflect>(
			std::visit([&] (const auto & query) -> sst::Reflect::Query {
				return analyze_reflect_query(query, info);
			}, refl.query),
			make_member_addrs(info.member_table),		
			type::Null{}
		);
	}
}