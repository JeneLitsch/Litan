#include "GlobalTable.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>
#include <iostream>
#include "namespace_resolution.hxx"

namespace ltn::c {
	namespace {
		CompilerError multiple_definitions(const ast::Global & fx) {
			std::stringstream msg;
			msg << "Global variable ";
			msg << fx.namespaze.to_string();
			msg << fx.name;
			msg	<< " already exists";
			return CompilerError{ msg.str(), {} };
		}
	}



	// returns function if defined or nultptr otherwise
	const ast::Global * ValidGlobalTable::resolve(
		const std::string_view name,
		const ast::Namespace & from,
		const ast::Namespace & to) {
		return ltn::c::resolve(this->enums, from, to, name);
	}



	const ast::Global * ValidGlobalTable::resolve(
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
	void ValidGlobalTable::insert(const ast::Global & e) {
		// Prevent redefinition
		if(this->resolve(e.name, e.namespaze)) {
			throw multiple_definitions(e);
		}
		this->enums.push_back(&e);
	}



	// returns function if defined or nultptr otherwise
	const ast::Global * InvalidGlobalTable::resolve(
		const std::string_view name,
		const ast::Namespace & from,
		const ast::Namespace & to) {
		throw CompilerError { "Cannot use globals inside " + this->inside };
	}



	const ast::Global * InvalidGlobalTable::resolve(
		const std::string_view name,
		const ast::Namespace & full) {
		throw CompilerError { "Cannot use globals inside " + this->inside };
	}



	// defines new function
	void InvalidGlobalTable::insert(const ast::Global & e) {
		throw CompilerError { "Cannot declare globals inside " + this->inside };
	}
}