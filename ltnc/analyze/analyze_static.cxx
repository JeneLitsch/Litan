#include "analyze.hxx"
#include <sstream>
#include "stdxx/iife.hxx"
#include "ltnc/sst/expr/Literal.hxx"



namespace ltn::c {
	namespace {
		auto analyze_static(
			auto make,
			const auto & statik,
			Context & context,
			std::uint64_t id) {

			MajorScope scope { statik.namespaze, Qualifiers::none, context};

			auto expr = statik.expr ? analyze_expression(*statik.expr, scope) : sst::expr::null();
			auto node = make(statik.name, statik.namespaze, std::move(expr), id);

			node->is_extern = statik.is_extern;
			node->is_private = statik.is_private;
			return node;
		}
	}



	sst::defn_ptr analyze_definition(
		const ast::decl::Definition & def,
		Context & context,
		std::uint64_t id) {
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
			.reporter          = context.reporter,
			.custom_resolver   = context.custom_resolver,
		};
		return analyze_static(sst::decl::definition, def, read_context, id);
	}



	sst::glob_ptr analyze_global(
		const ast::decl::Global & global,
		Context & context,
		std::uint64_t id) {
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
			.reporter          = context.reporter,
			.custom_resolver   = context.custom_resolver,
		};
		return analyze_static(sst::decl::variable, global, read_context, id);
	}
}