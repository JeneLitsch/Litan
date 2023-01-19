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



	namespace {
		std::vector<stx::reference<const ast::Functional>> find_extern_funtions(
			const ast::Program & source) {
			std::vector<stx::reference<const ast::Functional>> externs;
			for(const auto & fx : source.functions) {
				if(fx->is_extern) {
					externs.push_back(*fx);
				}
				if(fx->name == "main" && (fx->parameters.size() == 0 || fx->parameters.size() == 1)) {
					externs.push_back(*fx);
				}
			}
			return externs;
		}



		auto analyze_staged(const StagedFx & staged, Context & context) {
			return analyze_functional(*staged.fx, context); 
		}



		auto analyze_staged(const StagedTemplateFx & staged, Context & context) {
			return analyze_function_template(staged.tmpl, context, staged.arguments); 
		}
	}



	sst::Program analyze(
		const ast::Program & source,
		Reporter & reporter) {
		
		sst::Program program;
		ValidFunctionTable fx_table;
		FunctionQueue fx_queue;
		ValidFunctionTemplateTable fx_template_table;
		ValidDefinitionTable definition_table;
		MemberTable member_table;
		ValidGlobalTable global_table;
		Context context {
			.fx_table = fx_table,
			.fx_template_table = fx_template_table,
			.fx_queue = fx_queue,
			.definition_table = definition_table,
			.member_table = member_table,
			.global_table = global_table,
			.reporter = reporter,
		};



		for(auto & enym : source.enums) {
			auto definitions = analyze_enumeration(*enym);
			for(auto & definition : definitions) {
				program.definitions.push_back(std::move(definition));
			}
		}

		for(const auto & definition : source.definitions) {
			program.definitions.push_back(analyze_definition(*definition, context));
		}

		for(const auto & def : program.definitions) {
			context.definition_table.insert(*def);
		}



		for(const auto & global : source.globals) {
			program.globals.push_back(analyze_global(*global, context));
		}

		for(const auto & glob : program.globals) {
			context.global_table.insert(*glob);
		}


		std::vector<ast::func_ptr> ctors;
		for(auto & preset : source.presets) {
			auto ctor = generate_ctor(*preset);
			ctors.push_back(std::move(ctor));
		}

		for(const auto & fx_tmpl : source.function_templates) {
			const auto function_arity = std::size(fx_tmpl->fx->parameters);
			const auto template_arity = std::size(fx_tmpl->template_parameters);
			context.fx_template_table.insert(*fx_tmpl, function_arity, template_arity);
		}

		for(const auto & function : source.functions) {
			context.fx_table.insert(*function, function->parameters.size());
		}

		for(const auto & ctor : ctors) {
			context.fx_table.insert(*ctor, ctor->parameters.size());
		}

		auto externs = find_extern_funtions(source);

		for(const auto & function : externs) {
			fx_queue.stage_function(function);
		}

		while(auto staged = fx_queue.fetch_function()) {
			try {
				auto fx = std::visit([&] (auto & s) {
					return analyze_staged(s, context);
					}, *staged
				);
				program.functions.push_back(std::move(fx));
			}
			catch(const CompilerError & error) {
				reporter.push(error);
			}
		}

		return program;
	}

}
