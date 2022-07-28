#include "namespace_resolution.hxx"

namespace ltn::c {

	namespace {
		bool match(
			const ast::Functional & fx,
			const ast::Namespace & full,
			const std::string_view name,
			const std::size_t parameters) {

			return
				fx.name == name &&
				fx.namespaze == full &&
				std::size(fx.parameters) == parameters;
		}



		bool match(
			const ast::Definition & definition,
			const ast::Namespace & full,
			const std::string_view name) {

			return
				definition.name == name &&
				definition.namespaze == full;
		}


		
		bool match(
			const ast::Global & global,
			const ast::Namespace & full,
			const std::string_view name) {

			return
				global.name == name &&
				global.namespaze == full;
		}
	}



	template<typename DeclNode>
	const DeclNode * resolve_rec(
		const std::vector<const DeclNode *> & functions,
		const ast::Namespace & from,
		const ast::Namespace & to,
		const std::string_view name,
		const auto & ... additional) {

		for(const auto & fx : functions) {
			if(match(*fx, from + to, name, additional...)) {
				return fx;
			}
		}
		
		if(from.empty()) {
			return nullptr;
		}
		

		ast::Namespace outer = from;
		outer.pop_back();


		return resolve_rec(
			functions,
			outer,
			to,
			name,
			additional...);
	}



	template<typename DeclNode>
	const DeclNode * resolve_x(
		const std::vector<const DeclNode *> & decls,
		const ast::Namespace & from,
		const ast::Namespace & to,
		const std::string_view name,
		const auto & ... additional) {

		if(to.is_absolute()) {
			for(const auto & d : decls) {
				if(match(*d, to, name, additional...)) {
					return d;
				}
			}
			return nullptr;
		}
	
		return resolve_rec(decls, from, to, name, additional...);
	}



	const ast::Functional * resolve(
		const std::vector<const ast::Functional *> & functions,
		const ast::Namespace & from,
		const ast::Namespace & to,
		const std::string_view name,
		const std::size_t parameters) {

		return resolve_x(functions, from, to, name, parameters);
	}



	const ast::Definition * resolve(
		const std::vector<const ast::Definition *> & definition,
		const ast::Namespace & from,
		const ast::Namespace & to,
		const std::string_view name) {

		return resolve_x(definition, from, to, name);
	}



	const ast::Global * resolve(
		const std::vector<const ast::Global *> & globals,
		const ast::Namespace & from,
		const ast::Namespace & to,
		const std::string_view name) {
		return resolve_x(globals, from, to, name);
	}
}