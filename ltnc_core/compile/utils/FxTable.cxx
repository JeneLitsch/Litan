#include "FxTable.hxx"
#include "ltnc_core/CompilerError.hxx"
#include <sstream>
#include <iostream>
#include "ltn/printing.hxx"
namespace ltn::c::compile {
	CompilerError multiple_definitions(const ast::Functional & fx) {
		std::stringstream msg;
		msg << "Function ";
		msg << fx.name << "(";
		msg << std::size(fx.parameters);
		msg << ") already exists";
		return CompilerError{ msg.str(), {} };
	}



	namespace {
		template<class T>
		std::vector<T> operator+(
			const std::vector<T> & l,
			const std::vector<T> & r) {
			std::vector<T> vec;
			vec.reserve(l.size() + r.size());
			vec.insert(std::end(vec), l.begin(), l.end());
			vec.insert(std::end(vec), r.begin(), r.end());
			return vec;
		}



		const ast::Functional * resolve_rec(
			const std::vector<const ast::Functional *> & functions,
			const ast::Namespace & from,
			const ast::Namespace & to,
			const std::string_view name,
			const std::size_t parameters) {

			for(const auto & fx : functions) {
				const bool names_match = fx->name == name;
				const bool params_match = std::size(fx->parameters) == parameters;
				const bool namespaces_match = (from + to) == fx->namespaze;
				if(names_match && params_match && namespaces_match) {
					return fx;
				}
			}
			
			if(from.empty()) {
				return nullptr;
			}
			
			return resolve_rec(
				functions,
				{from.begin(), from.end()-1},
				to,
				name,
				parameters);
		}



		const ast::Functional * resolve(
			const std::vector<const ast::Functional *> & functions,
			const ast::Namespace & from,
			const ast::Namespace & to,
			const std::string_view name,
			const std::size_t parameters) {

			if(ast::is_absolute(to)) {
				for(const auto & fx : functions) {
					const bool names_match = fx->name == name;
					const bool params_match = std::size(fx->parameters) == parameters;
					const bool namespaces_match = fx->namespaze == ast::Namespace{to.begin()+1, to.end()};
					if(names_match && params_match && namespaces_match) {
						return fx;
					}
				}
				return nullptr;
			}
		
			return resolve_rec(functions, from, to, name, parameters);
		}
	}



	// returns function if defined or nultptr otherwise
	const ast::Functional * FxTable::resolve(
		const std::string_view name,
		const ast::Namespace & from,
		const ast::Namespace & to,
		const std::size_t parameters) {
		return compile::resolve(this->functions, from, to, name, parameters);
	}



	const ast::Functional * FxTable::resolve(
		const std::string_view name,
		const ast::Namespace & full,
		const std::size_t parameters) {
		return compile::resolve(this->functions, {}, full, name, parameters); 
	}



	// defines new function
	void FxTable::insert(const ast::Functional & fx) {
		if(fx.pr1vate && fx.namespaze.empty()) {
			throw CompilerError{"Private functions cannot be declared in global namespace", {}};
		}
		// Prevent redefinition
		if(this->resolve(fx.name, fx.namespaze, std::size(fx.parameters))) {
			throw multiple_definitions(fx);
		}
		this->functions.push_back(&fx);
	}
}