#include "DefinitionTable.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>
#include <iostream>
#include "namespace_resolution.hxx"

namespace ltn::c {
	namespace {
		CompilerError multiple_definitions(const ast::Definition & fx) {
			std::stringstream msg;
			msg << "Definition constant ";
			msg << fx.namespaze.to_string();
			msg << fx.name;
			msg	<< " already exists";
			return CompilerError{ msg.str(), {} };
		}
	}



	// returns function if defined or nultptr otherwise
	const ast::Definition * DefinitionTable::resolve(
		const std::string_view name,
		const ast::Namespace & from,
		const ast::Namespace & to) {
		return ltn::c::resolve(this->enums, from, to, name);
	}



	const ast::Definition * DefinitionTable::resolve(
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
	void DefinitionTable::insert(const ast::Definition & e) {
		// Prevent redefinition
		if(this->resolve(e.name, e.namespaze)) {
			throw multiple_definitions(e);
		}
		this->enums.push_back(&e);
	}
}