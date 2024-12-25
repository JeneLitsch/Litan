#include "namespace_resolution.hxx"

namespace ltn::c {

	namespace {
		
		bool match(
			const ast::decl::Function & fx,
			const Namespace & full,
			const std::string_view name,
			const std::size_t parameters,
			VariadicMode variadic_mode) {
				
			using VM = VariadicMode; 
			switch (variadic_mode) {

			case VM::EXACT:
				return
					fx.name == name &&
					fx.namespaze == full &&
					std::size(fx.parameters.simple) == parameters &&
					fx.parameters.variadic;
			
			case VM::REQUIRED:
				return
					fx.name == name &&
					fx.namespaze == full &&
					std::size(fx.parameters.simple) <= parameters &&
					fx.parameters.variadic;
			
			case VM::ALLOWED:
				return
					match(fx, full, name, parameters, VM::REQUIRED) ||
					match(fx, full, name, parameters, VM::PROHIBITED);
			
			case VM::PROHIBITED:
				return
					fx.name == name &&
					fx.namespaze == full &&
					std::size(fx.parameters.simple) == parameters &&
					!fx.parameters.variadic;
			}

			return false;
		}



		bool match(
			const sst::decl::Definition & definition,
			const Namespace & full,
			const std::string_view name) {

			return
				definition.name == name &&
				definition.namespaze == full;
		}


		
		bool match(
			const sst::decl::Global & global,
			const Namespace & full,
			const std::string_view name) {

			return
				global.name == name &&
				global.namespaze == full;
		}
	}



	template<typename DeclNode>
	const DeclNode * resolve_rec(
		const std::vector<const DeclNode *> & functions,
		const Namespace & from,
		const Namespace & to,
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
		

		Namespace outer = from;
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
		const Namespace & from,
		const Namespace & to,
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



	const ast::decl::Function * resolve(
		const std::vector<const ast::decl::Function *> & functions,
		const Namespace & from,
		const Namespace & to,
		const std::string_view name,
		const std::size_t parameters,
		VariadicMode variadic_mode) {

		return resolve_x(functions, from, to, name, parameters, variadic_mode);
	}



	const sst::decl::Definition * resolve(
		const std::vector<const sst::decl::Definition *> & definition,
		const Namespace & from,
		const Namespace & to,
		const std::string_view name) {

		return resolve_x(definition, from, to, name);
	}



	const sst::decl::Global * resolve(
		const std::vector<const sst::decl::Global *> & globals,
		const Namespace & from,
		const Namespace & to,
		const std::string_view name) {
		return resolve_x(globals, from, to, name);
	}
}