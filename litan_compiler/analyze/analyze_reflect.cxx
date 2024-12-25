#include "analyze.hxx"
#include <string_view>
#include <iostream>
#include "litan_compiler/ast/expr/Reflect.hxx"
#include "litan_compiler/sst/expr/Reflect.hxx"

namespace ltn::c {
	namespace {
		sst::expr::Reflect::FunctionQuery fx_to_query(const ast::decl::Function & fx) {
			return sst::expr::Reflect::FunctionQuery {
				.id          = make_function_label(fx).to_string(),
				.name        = fx.name,
				.full_name   = fx.namespaze.to_string() + fx.name,
				.arity       = fx.parameters.simple.size(),
				.c0nst       = fx.qualifiers.is_const,
				.pr1vate     = fx.qualifiers.is_private,
				.ext3rn      = fx.qualifiers.is_extern,
				.is_variadic = fx.parameters.variadic.has_value(),
			};
		}



		sst::expr::Reflect::Addr make_member_addrs(Scope & scope) {
			return sst::expr::Reflect::Addr {
				.name      = scope.resolve_member_id("name"),
				.full_name = scope.resolve_member_id("full_name"),
				.fx_ptr    = scope.resolve_member_id("fx_ptr"),
				.functions = scope.resolve_member_id("functions"),
				.c0nst     = scope.resolve_member_id("const"),
				.pr1vate   = scope.resolve_member_id("private"),
				.ext3rn    = scope.resolve_member_id("extern"),
				.file      = scope.resolve_member_id("file"),
				.line      = scope.resolve_member_id("line"),
				.type      = scope.resolve_member_id("type"),
			};
		}



		sst::expr::Reflect::FunctionQuery analyze_reflect_query(
			const ast::expr::Reflect & refl,
			const ast::expr::Reflect::FunctionQuery & query,
			Scope & scope) {

			auto fx = scope.resolve_function(
				query.name,
				query.namespaze,
				query.arity,
				query.is_variadic ? VariadicMode::REQUIRED : VariadicMode::PROHIBITED
			);

			if(!fx) throw undefined_function(query.name, location(refl));
			
			scope.require_function(*fx);
			return fx_to_query(*fx);
		}



		sst::expr::Reflect::NamespaceQuery analyze_reflect_query(
			const ast::expr::Reflect &,
			const ast::expr::Reflect::NamespaceQuery & query,
			Scope & scope) {
			
			sst::expr::Reflect::NamespaceQuery sst_query;
			sst_query.namespaze = query.namespaze;
			for(const auto & fx : scope.get_all_functions()) {
				if(fx->namespaze == query.namespaze) {
					scope.require_function(*fx);
					sst_query.functions.push_back(fx_to_query(*fx));
				}
			}
		
			return sst_query;
		}



		sst::expr::Reflect::LineQuery analyze_reflect_query(
			const ast::expr::Reflect & refl,
			const ast::expr::Reflect::LineQuery &,
			Scope &) {

			return sst::expr::Reflect::LineQuery {
				.line = location(refl).line 
			};
		}



		auto analyze_reflect_query(
			const ast::expr::Reflect & refl,
			const ast::expr::Reflect::FileQuery &,
			Scope &) {

			return sst::expr::Reflect::FileQuery {
				.name = location(refl).sourcename 
			};
		}



		auto analyze_reflect_query(
			const ast::expr::Reflect & refl,
			const ast::expr::Reflect::LocationQuery & query,
			Scope & scope) {

			return sst::expr::Reflect::LocationQuery {
				.file = analyze_reflect_query(refl, query.file, scope), 
				.line = analyze_reflect_query(refl, query.line, scope), 
			};
		}
	}



	// compiles array literal
	sst::expr_ptr analyze_expr(const ast::expr::Reflect & refl, Scope & scope) {
		return sst::expr::reflect(
			std::visit([&] (const auto & query) -> sst::expr::Reflect::Query {
				return analyze_reflect_query(refl, query, scope);
			}, refl.query),
			make_member_addrs(scope)	
		);
	}
}