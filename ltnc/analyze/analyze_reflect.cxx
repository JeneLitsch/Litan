#include "analyze.hxx"
#include <string_view>
#include <iostream>
namespace ltn::c {
	namespace {
		sst::Reflect::FunctionQuery fx_to_query(const ast::Functional & fx) {
			return sst::Reflect::FunctionQuery {
				.id        = make_function_label(fx).to_string(),
				.name      = fx.name,
				.full_name = fx.namespaze.to_string() + fx.name,
				.arity     = fx.parameters.size(),
				.c0nst     = fx.is_const,
				.pr1vate   = fx.is_private,
				.ext3rn    = fx.is_extern,
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
				.file      = member_table.get_id("file"),
				.line      = member_table.get_id("line"),
				.type      = member_table.get_id("type"),
			};
		}



		sst::Reflect::FunctionQuery analyze_reflect_query(
			const ast::Reflect & refl,
			const ast::Reflect::FunctionQuery & query,
			Context & context,
			Scope & scope) {

			const auto * fx = context.fx_table.resolve(
				query.name,
				query.namespaze,
				query.arity
			);

			if(!fx) {
				throw undefined_function(query.name, ast::Node{{}});
			}
			
			context.fx_queue.stage_function(*fx);
			return fx_to_query(*fx);
		}



		sst::Reflect::NamespaceQuery analyze_reflect_query(
			const ast::Reflect & refl,
			const ast::Reflect::NamespaceQuery & query,
			Context & context,
			Scope & scope) {

			sst::Reflect::NamespaceQuery sst_query;
			sst_query.namespaze = query.namespaze;
			for(const auto & fx : context.fx_table.get_symbols()) {
				if(fx->namespaze == query.namespaze) {
					context.fx_queue.stage_function(*fx);
					sst_query.functions.push_back(fx_to_query(*fx));
				}
			}
		
			return sst_query;
		}



		sst::Reflect::LineQuery analyze_reflect_query(
			const ast::Reflect & refl,
			const ast::Reflect::LineQuery & query,
			Context & context,
			Scope & scope) {

			return sst::Reflect::LineQuery {
				.line = refl.location.line 
			};
		}



		auto analyze_reflect_query(
			const ast::Reflect & refl,
			const ast::Reflect::FileQuery & query,
			Context & context,
			Scope & scope) {

			return sst::Reflect::FileQuery {
				.name = refl.location.sourcename 
			};
		}



		auto analyze_reflect_query(
			const ast::Reflect & refl,
			const ast::Reflect::LocationQuery & query,
			Context & context,
			Scope & scope) {

			return sst::Reflect::LocationQuery {
				.file = analyze_reflect_query(refl, query.file, context, scope), 
				.line = analyze_reflect_query(refl, query.line, context, scope), 
			};
		}



		auto analyze_reflect_query(
			const ast::Reflect & refl,
			const ast::Reflect::ExprQuery & query,
			Context & context,
			Scope & scope) {
			
			const auto expr = analyze_expression(*query.expr, context, scope);

			return sst::Reflect::ExprQuery {
				.type_query = sst::Reflect::TypeQuery{
					.type = expr->type
				}
			};
		}



		auto analyze_reflect_query(
			const ast::Reflect & refl,
			const ast::Reflect::TypeQuery & query,
			Context & context,
			Scope & scope) {

			return sst::Reflect::TypeQuery {
				.type = instantiate_type(query.type, scope)
			};
		}
	}



	// compiles array literal
	sst::expr_ptr analyze_expr(
		const ast::Reflect & refl,
		Context & context,
		Scope & scope) {
			
		return std::make_unique<sst::Reflect>(
			std::visit([&] (const auto & query) -> sst::Reflect::Query {
				return analyze_reflect_query(refl, query, context, scope);
			}, refl.query),
			make_member_addrs(context.member_table),		
			type::Any{}
		);
	}
}