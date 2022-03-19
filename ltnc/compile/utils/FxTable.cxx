#include "FxTable.hxx"
#include "ltnc_core/CompilerError.hxx"
#include <sstream>
#include <iostream>
#include "ltn/printing.hxx"
namespace ltn::c::compile {
	CompilerError multiple_definitions(const FxSignature & fx) {
		std::stringstream msg;
		msg << "Function ";
		msg << fx.name << "(";
		msg << fx.parameters;
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

		const FxSignature * resolve_rec(
			const std::vector<FxSignature> & functions,
			const ast::Namespace & from,
			const ast::Namespace & to,
			const std::string_view name,
			const std::size_t parameters) {

			for(const auto & fx : functions) {
				const bool names_match = fx.name == name;
				const bool params_match = fx.parameters == parameters;
				const bool namespaces_match = (from + to) == fx.namespaze;
				if(names_match && params_match && namespaces_match) {
					return &fx;
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

		const FxSignature * resolve(
			const std::vector<FxSignature> & functions,
			const ast::Namespace & from,
			const ast::Namespace & to,
			const std::string_view name,
			const std::size_t parameters) {

			if(ast::is_absolute(to)) {
				for(const auto & fx : functions) {
					const bool names_match = fx.name == name;
					const bool params_match = fx.parameters == parameters;
					const bool namespaces_match = fx.namespaze == ast::Namespace{to.begin()+1, to.end()};
					if(names_match && params_match && namespaces_match) {
						return &fx;
					}
				}
				return nullptr;
			}
		
			return resolve_rec(functions, from, to, name, parameters);
		}
	}

	// returns function if defined or nultptr otherwise
	const FxSignature * FxTable::resolve(
		const std::string_view name,
		const ast::Namespace & from,
		const ast::Namespace & to,
		const std::size_t parameters) {
		return ltn::c::compile::resolve(this->functions, from, to, name, parameters);
	}

	const FxSignature * FxTable::resolve(
		const std::string_view name,
		const ast::Namespace & full,
		const std::size_t parameters) {
		for(const auto & fx : this->functions) {
			if(
				fx.name == name &&
				fx.parameters == parameters &&
				fx.namespaze == full) {
				return &fx;
			}
		}
		return nullptr;
	}

	// defines new function
	void FxTable::insert(const FxSignature & fx) {
		// Prevent redefinition
		if(this->resolve(fx.name, fx.namespaze, fx.parameters)) {
			throw multiple_definitions(fx);
		}
		this->functions.push_back(fx);
	}
}