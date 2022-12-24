#include "analyze.hxx"

namespace ltn::c {
	sst::defn_ptr analyze_definition(const ast::Definition & def, Context & context) {
		// Use empty global_table to prohibit the usage of other global variables.
		// Functions or defines can be used though.
		InvalidDefinitionTable def_table { "definitions" };
		InvalidGlobalTable global_table { "definitions" };
		InvalidFunctionTable fx_table { "definitions" };
		InvalidOverloadTable overload_table { "definitions" };
		InvalidFunctionTemplateTable fx_template_table { "definitions" };
		Context read_context {
			.fx_table          = fx_table,
			.fx_template_table = fx_template_table,
			.fx_queue		   = context.fx_queue,
			.overload_table    = overload_table,
			.definition_table  = def_table,
			.member_table      = context.member_table,
			.global_table      = global_table,
			.reporter          = context.reporter
		};
		MajorScope scope { def.namespaze, false };
		auto sst_def = std::make_unique<sst::Definition>(
			def.name,
			def.namespaze,
			instantiate_type(def.type, scope)
		);
		if(def.expr) {
			sst_def->expr = analyze_expression(*def.expr, read_context, scope);
		}
		return sst_def;
	}
}