#include "stdxx/functional.hxx"
#include "analyze.hxx"
#include "ltnc/ast/expr/Var.hxx"

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



		auto analyze_staged(const StagedFunction & staged, RootScope & root_scope) {
			NamespaceScope namespace_scope {
				root_scope,
				staged.override_namespace.value_or(staged.fx->namespaze),
			};
			FunctionScope function_scope {
				namespace_scope,
				staged.fx->qualifiers,
			};
			auto label = make_function_label(staged.fx);
			static const std::vector<std::unique_ptr<ast::expr::Var>> no_captures;
			return analyze_function(staged.fx, function_scope, label, staged.captures.value_or(no_captures)); 
		}
	}



	sst::Program analyze(
		const ast::Program & source,
		const std::vector<ltn::c::CustomLiteral> & literals) {
		
		sst::Program program;
		ValidFunctionTable fx_table;
		FunctionQueue fx_queue;
		ValidDefinitionTable definition_table;
		ValidGlobalTable global_table;
		CustomResolver custom_resolver{literals};
		Context context {
			.fx_table = fx_table,
			.fx_queue = fx_queue,
			.definition_table = definition_table,
			.global_table = global_table,
			.custom_resolver = custom_resolver,
		};
		RootScope root_scope { context };

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
			root_scope.add_namespace(function->namespaze);
		}

		auto externs = find_extern_funtions(source);

		for(const auto & function : externs) {
			fx_queue.stage_function(function);
		}

		while(auto staged = fx_queue.fetch_function()) {
			auto fx = analyze_staged(*staged, root_scope);
			program.functions.push_back(std::move(fx));
		}

		for(auto & [name, info] : root_scope.get_member_info_table()) {
			program.member_name_table[name] = info.id;
		}

		return program;
	}

}
