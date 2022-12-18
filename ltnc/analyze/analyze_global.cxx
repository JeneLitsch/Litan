#include "analyze.hxx"
#include <sstream>
namespace ltn::c {
	namespace {
		auto undefined(const ast::GlobalVar & global) {
			std::ostringstream oss;
			oss
				<< "Undefined global variable "
				<< global.namespaze.to_string() << global.name;

			return CompilerError { oss.str(), global.location };
		}

		auto undefined(const ast::Var & def) {
			std::ostringstream oss;
			oss
				<< "Undefined definition "
				<< def.namespaze.to_string() << def.name;

			return CompilerError { oss.str(), def.location };
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



	sst::expr_ptr analyze_write_global(
		const ast::GlobalVar & global_var,
		Context & context,
		Scope & scope) {

		const auto & global = resolve_static(global_var, context.global_table, scope);
		return std::make_unique<sst::GlobalVar>(global.type, global.id);
	}



	sst::expr_ptr analyze_write_define(
		const ast::Var & def,
		Context & context,
		Scope & scope) {

		const auto & statik = resolve_static(def, context.definition_table, scope);
		return std::make_unique<sst::Var>(statik.id, statik.type);
	}
}