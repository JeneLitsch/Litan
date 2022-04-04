#include "GlobalTable.hxx"
#include "ltnc_core/CompilerError.hxx"
#include <sstream>
#include <iostream>
#include "ltn/printing.hxx"
namespace ltn::c::compile {

	CompilerError multiple_definitions(const ast::Global & fx) {
		std::stringstream msg;
		msg << "Global constant ";
		for(const auto & step : fx.namespaze) {
			msg << step << "::";
		}
		msg << fx.name;
		msg	<< " already exists";
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



		const ast::Global * resolve_rec(
			const std::vector<const ast::Global *> & globals,
			const ast::Namespace & from,
			const ast::Namespace & to,
			const std::string_view name) {

			for(const auto & e : globals) {
				const bool names_match = e->name == name;
				const bool namespaces_match = (from + to) == e->namespaze;
				if(names_match && namespaces_match) {
					return e;
				}
			}
			
			if(from.empty()) {
				return nullptr;
			}
			
			return resolve_rec(
				globals,
				{from.begin(), from.end()-1},
				to,
				name);
		}



		const ast::Global * resolve(
			const std::vector<const ast::Global *> & globals,
			const ast::Namespace & from,
			const ast::Namespace & to,
			const std::string_view name) {

			if(ast::is_absolute(to)) {
				for(const auto & e : globals) {
					const bool names_match = e->name == name;
					const bool namespaces_match = e->namespaze == ast::Namespace{to.begin()+1, to.end()};
					if(names_match && namespaces_match) {
						return e;
					}
				}
				return nullptr;
			}
		
			return resolve_rec(globals, from, to, name);
		}
	}



	// returns function if defined or nultptr otherwise
	const ast::Global * GlobalTable::resolve(
		const std::string_view name,
		const ast::Namespace & from,
		const ast::Namespace & to) {
		return ltn::c::compile::resolve(this->enums, from, to, name);
	}



	const ast::Global * GlobalTable::resolve(
		const std::string_view name,
		const ast::Namespace & full) {
		for(const auto & e : this->enums) {
			if(
				e->name == name &&
				e->namespaze == full) {
				return e;
			}
		}
		return nullptr;
	}



	// defines new function
	void GlobalTable::insert(const ast::Global & e) {
		// Prevent redefinition
		if(this->resolve(e.name, e.namespaze)) {
			throw multiple_definitions(e);
		}
		this->enums.push_back(&e);
	}
}