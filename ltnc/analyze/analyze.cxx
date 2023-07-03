#include "stdxx/functional.hxx"
#include "analyze.hxx"

namespace ltn::c {
	namespace {
		std::vector<stx::reference<const ast::Function>> find_extern_funtions(
			const ast::Program & source) {
			std::vector<stx::reference<const ast::Function>> externs;
			for(const auto & fx : source.functions) {
				if(fx->is_extern) {
					externs.push_back(*fx);
				}
				if(fx->name == "main" && (fx->parameters.simple.size() == 0 || fx->parameters.simple.size() == 1)) {
					externs.push_back(*fx);
				}
			}
			return externs;
		}



		auto analyze_staged(const Staged & staged, Context & context) {
			FunctionScope scope {
				staged.override_namespace.value_or(staged.fx->namespaze),
				staged.fx->is_const,
				context,
			};
			auto label = make_function_label(staged.fx);
			static const std::vector<std::unique_ptr<ast::Var>> no_captures;
			return analyze_functional(staged.fx, scope, label, staged.captures.value_or(no_captures)); 
		}
	}



	std::vector<sst::expr_ptr> analyze_all_expressions(const std::vector<ast::expr_ptr> & exprs, Scope & scope) {
		auto analyze_all = stx::fx::mapped([&] (const auto & expr) {
			return analyze_expression(*expr, scope);
		});
		return analyze_all(exprs);
	}



	sst::Program analyze(
		const ast::Program & source,
		Reporter & reporter,
		const std::vector<ltn::c::CustomLiteral> & literals) {
		
		sst::Program program;
		ValidFunctionTable fx_table;
		FunctionQueue fx_queue;
		ValidDefinitionTable definition_table;
		MemberTable member_table;
		ValidGlobalTable global_table;
		CustomResolver custom_resolver{literals};
		Context context {
			.fx_table = fx_table,
			.fx_queue = fx_queue,
			.definition_table = definition_table,
			.member_table = member_table,
			.global_table = global_table,
			.reporter = reporter,
			.custom_resolver = custom_resolver,
		};


		std::uint64_t global_counter = 0;


		for(auto & enym : source.enums) {
			auto definitions = analyze_enumeration(*enym, global_counter);
			for(auto & definition : definitions) {
				program.definitions.push_back(std::move(definition));
			}
		}

		for(const auto & definition : source.definitions) {
			program.definitions.push_back(analyze_definition(*definition, context, global_counter++));
		}

		for(const auto & def : program.definitions) {
			context.definition_table.insert(*def);
		}



		for(const auto & global : source.globals) {
			program.globals.push_back(analyze_global(*global, context, global_counter++));
		}

		for(const auto & glob : program.globals) {
			context.global_table.insert(*glob);
		}

		for(const auto & function : source.functions) {
			context.fx_table.insert(*function, function->parameters.simple.size(), VariadicMode::ALLOWED);
		}

		auto externs = find_extern_funtions(source);

		for(const auto & function : externs) {
			fx_queue.stage_function(function);
		}

		while(auto staged = fx_queue.fetch_function()) {
			try {
				auto fx = analyze_staged(*staged, context);
				program.functions.push_back(std::move(fx));
			}
			catch(const CompilerError & error) {
				reporter.push(error);
			}
		}

		program.member_name_table = member_table.get_table();

		return program;
	}

}
