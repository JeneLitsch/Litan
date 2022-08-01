#include "FxTable.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>
#include <iostream>
#include "namespace_resolution.hxx"
namespace ltn::c {

	CompilerError multiple_definitions(const ast::Functional & fx) {
		std::stringstream msg;
		msg << "Function ";
		msg << fx.namespaze.to_string();
		msg << fx.name << "(";
		msg << std::size(fx.parameters);
		msg << ") already exists";
		return CompilerError{ msg.str(), {} };
	}



	// returns function if defined or nultptr otherwise
	const ast::Functional * ValidFxTable::resolve(
		const std::string_view name,
		const ast::Namespace & from,
		const ast::Namespace & to,
		const std::size_t parameters) {
		return ltn::c::resolve(this->functions, from, to, name, parameters);
	}



	const ast::Functional * ValidFxTable::resolve(
		const std::string_view name,
		const ast::Namespace & full,
		const std::size_t parameters) {
		return ltn::c::resolve(this->functions, {}, full, name, parameters); 
	}



	// defines new function
	void ValidFxTable::insert(const ast::Functional & fx) {
		if(fx.pr1vate && fx.namespaze.empty()) {
			throw CompilerError{"Private functions cannot be declared in global namespace", {}};
		}
		// Prevent redefinition
		if(this->resolve(fx.name, fx.namespaze, std::size(fx.parameters))) {
			throw multiple_definitions(fx);
		}
		this->functions.push_back(&fx);
	}



	// returns function if defined or nultptr otherwise
	const ast::Functional * InvalidFxTable::resolve(
		const std::string_view name,
		const ast::Namespace & from,
		const ast::Namespace & to,
		const std::size_t parameters) {
		throw CompilerError { "Cannot use functions inside " + this->inside };
	}



	const ast::Functional * InvalidFxTable::resolve(
		const std::string_view name,
		const ast::Namespace & full,
		const std::size_t parameters) {
		throw CompilerError { "Cannot use functions inside " + this->inside };
	}



	// defines new function
	void InvalidFxTable::insert(const ast::Functional & fx) {
		throw CompilerError { "Cannot declare functions inside " + this->inside };
	}
}