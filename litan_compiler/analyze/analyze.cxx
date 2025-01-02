#include "stdxx/functional.hxx"
#include "analyze.hxx"
#include "litan_compiler/ast/expr/Var.hxx"
#include "optimize/optimize.hxx"

namespace ltn::c {
	namespace {
		std::vector<stx::reference<const ast::decl::Function>> find_extern_funtions(
			const ast::Program & source) {
			std::vector<stx::reference<const ast::decl::Function>> externs;
			for(const auto & fx : source.functions) {
				if(fx->qualifiers.is_extern) {
					externs.push_back(*fx);
				}
				if(fx->name == "main" && (fx->parameters.simple.size() == 0 || fx->parameters.simple.size() == 1)) {
					externs.push_back(*fx);
				}
			}
			return externs;
		}



		auto analyze_staged(const StagedFunction & staged, Context & context) {
			FunctionScope scope {
				staged.override_namespace.value_or(staged.fx->namespaze),
				staged.fx->qualifiers,
				context,
			};
			auto label = make_function_label(staged.fx);
			static const std::vector<std::unique_ptr<ast::expr::Var>> no_captures;
			return analyze_function(staged.fx, scope, label, staged.captures.value_or(no_captures)); 
		}
	}



	sst::Program analyze(const ast::Program & ast, const AnalysisOptions & options) {
		
		sst::Program program;
		ValidFunctionTable fx_table;
		FunctionQueue fx_queue;
		ValidDefinitionTable definition_table;
		MemberTable member_table;
		ValidGlobalTable global_table;
		CustomResolver custom_resolver{{}};
		Context context {
			.fx_table = fx_table,
			.fx_queue = fx_queue,
			.definition_table = definition_table,
			.member_table = member_table,
			.global_table = global_table,
			.custom_resolver = custom_resolver,
		};


		std::uint64_t global_counter = 0;



		for(auto & enym : ast.enums) {
			auto definitions = analyze_enumeration(*enym, global_counter);
			for(auto & definition : definitions) {
				program.definitions.push_back(std::move(definition));
			}
		}

		

		for(const auto & definition : ast.definitions) {
			program.definitions.push_back(analyze_definition(*definition, context, global_counter++));
		}

		for(const auto & def : program.definitions) {
			context.definition_table.insert(*def);
		}



		for(const auto & global : ast.globals) {
			program.globals.push_back(analyze_global(*global, context, global_counter++));
		}

		for(const auto & glob : program.globals) {
			context.global_table.insert(*glob);
		}



		for(const auto & function : ast.functions) {
			context.fx_table.insert(*function, function->parameters.simple.size(), VariadicMode::ALLOWED);
		}

		auto externs = find_extern_funtions(ast);

		for(const auto & function : externs) {
			fx_queue.stage_function(function);
		}

		while(auto staged = fx_queue.fetch_function()) {
			auto fx = analyze_staged(*staged, context);
			program.functions.push_back(std::move(fx));
		}

		for(const auto & [member_name, member_id] : member_table.get_table()) {
			program.member_name_table.insert(member_id, member_name);
		}


		if (options.optimize) {
			optimize(program);
		}
		return program;
	}

}
