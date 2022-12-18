#include "stdxx/functional.hxx"
#include "analyze.hxx"

namespace ltn::c {
	void add_template_args(
		Scope & scope,
		const std::vector<std::string> & template_params,
		const std::vector<type::IncompleteType> & template_args) {
		const auto arguments = stx::fx::map(instantiate_type, template_args, scope);
		return add_template_args(scope, template_params, arguments);
	}


	void add_template_args(
		Scope & scope,
		const std::vector<std::string> & template_params,
		const std::vector<type::Type> & template_args) {
		for(std::size_t i = 0; i < template_args.size(); ++i) {
			scope.add_type(template_params[i], template_args[i]);
		}
	}


	stx::reference<const ast::FunctionTemplate> get_template(
		const std::string & name,
		const Namespace & namespaze,
		const std::size_t function_arity,
		const std::size_t template_arity,
		const SourceLocation & location,
		Context & context,
		Scope & scope) {
		const auto * tmpl = context.fx_template_table.resolve(
			name,
			scope.get_namespace(),
			namespaze,
			function_arity,
			template_arity
		);
		if(!tmpl) {
			std::ostringstream oss;
			oss 
				<< "Cannot find template " 
				<< namespaze.to_string() << name
				<< " with " << template_arity << " arguements";
			throw CompilerError{oss.str(), location};
		}
		return *tmpl;
	}



	std::string make_template_id(
		const ast::Functional & fx,
		const std::vector<type::Type> & arguments) {
		
		std::ostringstream oss;
		oss << "<";
		oss << fx.get_resolve_namespace().to_string();
		oss << fx.get_resolve_name();
		oss << ":";
		bool first = true;
		for(const auto & arg : arguments) {
			if(first) {
				first = false;
			}
			else {
				oss << ",";
			}
			oss << type::to_string(arg);
		} 
		oss << ">"; 
		oss << "(" << fx.parameters.size() << ")";
		return oss.str();
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

		auto sst_def = std::make_unique<sst::Global>(
			global.name,
			global.namespaze,
			instantiate_type(global.type, scope)
		);
		if(global.expr) {
			sst_def->expr = analyze_expression(*global.expr, read_context, scope);
		}
		return sst_def;
	}



	sst::defn_ptr analyze_definition(const ast::Definition & def, Context & context) {
		// Use empty global_table to prohibit the usage of other global variables.
		// Functions or defines can be used though.
		InvalidDefinitionTable def_table { "definitions" };
		InvalidGlobalTable global_table { "definitions" };
		InvalidFunctionTable fx_table { "definitions" };
		InvalidFunctionTemplateTable fx_template_table { "definitions" };
		Context read_context {
			.fx_table          = fx_table,
			.fx_template_table = fx_template_table,
			.fx_queue		   = context.fx_queue,
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
