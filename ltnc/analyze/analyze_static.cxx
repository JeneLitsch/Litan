#include "analyze.hxx"
#include <sstream>
#include "stdxx/iife.hxx"
#include "ltnc/sst/expr/Literal.hxx"

#include "ltnc/scoping/DefinitionScope.hxx"
#include "ltnc/scoping/GlobalVariableScope.hxx"

namespace ltn::c {
	namespace {
		auto analyze_static(
			auto make,
			const auto & statik,
			Scope & scope,
			std::uint64_t id) {


			auto expr = statik.expr ? analyze_expression(*statik.expr, scope) : sst::expr::null();
			auto node = make(statik.name, statik.namespaze, std::move(expr), id);

			node->is_extern = statik.is_extern;
			node->is_private = statik.is_private;
			return node;
		}
	}



	sst::defn_ptr analyze_definition(
		const ast::decl::Definition & def,
		RootScope & root_scope,
		std::uint64_t id) {
		
		NamespaceScope namespace_scope { root_scope, def.namespaze };
		DefinitionScope static_scope { namespace_scope };

		return analyze_static(sst::decl::definition, def, static_scope, id);
	}



	sst::glob_ptr analyze_global(
		const ast::decl::Global & global,
		RootScope & root_scope,
		std::uint64_t id) {

		NamespaceScope namespace_scope { root_scope, global.namespaze };
		GlobalVariableScope static_scope { namespace_scope };

		return analyze_static(sst::decl::variable, global, static_scope, id);
	}
}