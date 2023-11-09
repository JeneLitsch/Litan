#include "analyze.hxx"
#include <string_view>
#include <iostream>
#include "ltnc/sst/expr/Reflect.hxx"

namespace ltn::c {
	namespace {
		sst::expr::Reflect::FunctionQuery fx_to_query(const ast::Function & fx) {
			return sst::expr::Reflect::FunctionQuery {
				.id          = make_function_label(fx).to_string(),
				.name        = fx.name,
				.full_name   = fx.namespaze.to_string() + fx.name,
				.arity       = fx.parameters.simple.size(),
				.c0nst       = fx.is_const,
				.pr1vate     = fx.is_private,
				.ext3rn      = fx.is_extern,
				.is_variadic = fx.parameters.variadic.has_value(),
			};
		}



		sst::expr::Reflect::Addr make_member_addrs(MemberTable & member_table) {
			return sst::expr::Reflect::Addr {
				.name      = member_table.get_id("name"),
				.full_name = member_table.get_id("full_name"),
				.fx_ptr    = member_table.get_id("fx_ptr"),
				.functions = member_table.get_id("functions"),
				.c0nst     = member_table.get_id("const"),
				.pr1vate   = member_table.get_id("private"),
				.ext3rn    = member_table.get_id("extern"),
				.file      = member_table.get_id("file"),
				.line      = member_table.get_id("line"),
				.type      = member_table.get_id("type"),
			};
		}



		sst::expr::Reflect::FunctionQuery analyze_reflect_query(
			const ast::Reflect & refl,
			const ast::Reflect::FunctionQuery & query,
			Scope & scope) {

			auto & context = scope.get_context();

			auto fx = scope.resolve_function(
				query.name,
				query.namespaze,
				query.arity,
				query.is_variadic ? VariadicMode::REQUIRED : VariadicMode::PROHIBITED
			);

			if(!fx) throw undefined_function(query.name, location(refl));
			
			context.fx_queue.stage_function(*fx);
			return fx_to_query(*fx);
		}



		sst::expr::Reflect::NamespaceQuery analyze_reflect_query(
			const ast::Reflect &,
			const ast::Reflect::NamespaceQuery & query,
			Scope & scope) {
			
			auto & context = scope.get_context();

			sst::expr::Reflect::NamespaceQuery sst_query;
			sst_query.namespaze = query.namespaze;
			for(const auto & fx : context.fx_table.get_symbols()) {
				if(fx->namespaze == query.namespaze) {
					context.fx_queue.stage_function(*fx);
					sst_query.functions.push_back(fx_to_query(*fx));
				}
			}
		
			return sst_query;
		}



		sst::expr::Reflect::LineQuery analyze_reflect_query(
			const ast::Reflect & refl,
			const ast::Reflect::LineQuery &,
			Scope &) {

			return sst::expr::Reflect::LineQuery {
				.line = location(refl).line 
			};
		}



		auto analyze_reflect_query(
			const ast::Reflect & refl,
			const ast::Reflect::FileQuery &,
			Scope &) {

			return sst::expr::Reflect::FileQuery {
				.name = location(refl).sourcename 
			};
		}



		auto analyze_reflect_query(
			const ast::Reflect & refl,
			const ast::Reflect::LocationQuery & query,
			Scope & scope) {

			return sst::expr::Reflect::LocationQuery {
				.file = analyze_reflect_query(refl, query.file, scope), 
				.line = analyze_reflect_query(refl, query.line, scope), 
			};
		}
	}



	// compiles array literal
	sst::expr_ptr analyze_expr(const ast::Reflect & refl, Scope & scope) {
		auto & context = scope.get_context();
			
		return sst::expr::reflect(
			std::visit([&] (const auto & query) -> sst::expr::Reflect::Query {
				return analyze_reflect_query(refl, query, scope);
			}, refl.query),
			make_member_addrs(context.member_table)	
		);
	}
}