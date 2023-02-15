#include "analyze.hxx"
#include <sstream>
namespace ltn::c {
	namespace {
		auto undefined(const ast::GlobalVar & global) {
			std::ostringstream oss;
			oss
				<< "Undefined global variable "
				<< global.namespaze.to_string() << global.name;

			return CompilerError { oss.str(), location(global) };
		}

		auto & resolve_static(const auto & statik, auto & table, Scope & scope) {
			const auto static_var = table.resolve(
				statik.name,
				scope.get_namespace(),
				statik.namespaze);

			if(!static_var) throw undefined(statik);
			return *static_var;
		}
	}



	sst::expr_ptr analyze_expr(
		const ast::GlobalVar & global_var,
		Context & context,
		Scope & scope) {
		
		auto & global = resolve_static(global_var, context.global_table, scope);

		return std::make_unique<sst::GlobalVar>(global.type, global.id);
	}



	sst::glob_ptr analyze_global(const ast::Global & global, Context & context) {
		// Use empty global_table to prohibit the usage of other global variables.
		// Functions or defines can be used though.
		InvalidGlobalTable global_table { "the default value of another global variable" };
		InvalidFunctionTable fx_table { "the initialization of a global variable" };
		InvalidFunctionTemplateTable fx_template_table { "the initialization of a global variable" };
		Context read_context {
			.fx_table          = fx_table,
			.fx_template_table = fx_template_table,
			.fx_queue		   = context.fx_queue,
			.definition_table  = context.definition_table,
			.member_table      = context.member_table,
			.global_table      = global_table,
			.reporter          = context.reporter
		};
		MajorScope scope { global.namespaze, false };

		auto type = instantiate_type(global.type, scope);
		auto expr = global.expr ? analyze_expression(global.expr, read_context, scope) : nullptr;

		return std::make_unique<sst::Global>(
			global.name,
			global.namespaze,
			std::move(type),
			std::move(expr)
		);
	}
}