#include "analyze.hxx"
#include <sstream>
#include "stdxx/iife.hxx"
#include "ltnc/analyze/default_value.hxx"

namespace ltn::c {
	namespace {
		type::Type deduce_type(
			const ast::Static & statik,
			const sst::expr_ptr & expr,
			Scope & scope) {
			if(statik.type) {
				return instantiate_type(*statik.type, scope);
			}
			else {
				return expr ? expr->type : type::Any{};
			}
		}



		template<typename NodeT>
		auto analyze_static(const auto & statik, Context & context) {

			MajorScope scope { statik.namespaze, false, context};

			auto expr = statik.expr ? analyze_expression(*statik.expr, scope) : nullptr;
			auto type = deduce_type(statik, expr, scope);

			if(!expr) {
				expr = generate_default_value(type, location(statik));
			}

			return std::make_unique<NodeT>(
				statik.name,
				statik.namespaze,
				std::move(type),
				std::move(expr)
			);
		}
	}



	sst::defn_ptr analyze_definition(
		const ast::Definition & def,
		Context & context) {
		// Use empty global_table to prohibit the usage of other global variables.
		// Functions or defines can be used though.
		InvalidDefinitionTable def_table { "definitions" };
		InvalidGlobalTable global_table { "definitions" };
		InvalidFunctionTable fx_table { "definitions" };
		Context read_context {
			.fx_table          = fx_table,
			.fx_queue		   = context.fx_queue,
			.definition_table  = def_table,
			.member_table      = context.member_table,
			.global_table      = global_table,
			.reporter          = context.reporter
		};
		return analyze_static<sst::Definition>(def, read_context);
	}



	sst::glob_ptr analyze_global(const ast::Global & global, Context & context) {
		// Use empty global_table to prohibit the usage of other global variables.
		// Functions or defines can be used though.
		InvalidGlobalTable global_table { "the default value of another global variable" };
		InvalidFunctionTable fx_table { "the initialization of a global variable" };
		Context read_context {
			.fx_table          = fx_table,
			.fx_queue		   = context.fx_queue,
			.definition_table  = context.definition_table,
			.member_table      = context.member_table,
			.global_table      = global_table,
			.reporter          = context.reporter
		};
		return analyze_static<sst::Global>(global, read_context);
	}
}