#include "Scope.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c::compile {
	Scope::Scope(const ast::Namespace & nameSpace) 
		: parent(nullptr), nameSpace(nameSpace) {

	}

	Scope::Scope(const Scope * parent) 
		: parent(parent), nameSpace(parent->nameSpace) {}

	// tries to resolve variable recursively
	Variable Scope::resolve(
		const std::string & name,
		std::size_t line) const{
		
		if(this->vars.contains(name)) {
			return this->vars.at(name);
		}
		else if(this->parent) {
			return this->parent->resolve(name, line);
		}
		throw CompilerError{"Undefined variable " + name, line};
	}

	// defines new variable and prevents disambiguations
	// Variables in outer scope can not be hidden
	Variable Scope::insert(
		const std::string & name,
		Variable::Qualifier qualifier,
		std::size_t line) {
		if(this->vars.contains(name)) {
			throw CompilerError{"Redefintion of variable " + name, line};
		}
		const auto addr = recSize();
		const Variable var{addr, qualifier}; 
		this->vars.insert({name, var});
		return var;
	}

	Variable Scope::insert(const std::string & name, std::size_t line) {
		return this->insert(name, Variable::Qualifier::MUTABLE, line);
	}


	// size of all stacked scopes combined
	std::uint64_t ltn::c::compile::Scope::recSize() const {
		if(this->parent) {
			return this->vars.size() + parent->recSize();
		}
		return this->vars.size();
	}


	const ltn::c::ast::Namespace & ltn::c::compile::Scope::getNamespace() const {
		return this->nameSpace;
	}

}

