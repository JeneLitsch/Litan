#include "GlobalTable.hxx"
#include "ltnc_core/CompilerError.hxx"
#include <sstream>
#include <iostream>
#include "ltn/printing.hxx"
#include "namespace_resolution.hxx"

namespace ltn::c::compile {
	namespace {
		CompilerError multiple_definitions(const ast::Global & fx) {
			std::stringstream msg;
			msg << "Global constant ";
			msg << fx.namespaze.to_string();
			msg << fx.name;
			msg	<< " already exists";
			return CompilerError{ msg.str(), {} };
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