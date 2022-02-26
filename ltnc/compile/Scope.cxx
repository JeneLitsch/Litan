#include "Scope.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c::compile {
	Scope::Scope(const ast::Namespace & namespaze) 
		: parent(nullptr), namespaze(namespaze) {

	}

	Scope::Scope(const Scope * parent) 
		: parent(parent), namespaze(parent->namespaze) {}

	// tries to resolve variable recursively
	Variable Scope::resolve(
		const std::string & name,
		const SourceLocation & location) const{
		
		if(this->vars.contains(name)) {
			return this->vars.at(name);
		}
		else if(this->parent) {
			return this->parent->resolve(name, location);
		}
		throw CompilerError{"Undefined variable " + name, location};
	}

	// defines new variable and prevents disambiguations
	// Variables in outer scope can not be hidden
	Variable Scope::insert(
		const std::string & name,
		Variable::Qualifier qualifier,
		const SourceLocation & location) {
		if(this->vars.contains(name)) {
			throw CompilerError{"Redefintion of variable " + name, location};
		}
		const auto addr = recSize();
		const Variable var{addr, qualifier}; 
		this->vars.insert({name, var});
		return var;
	}

	Variable Scope::insert(const std::string & name, const SourceLocation & location) {
		return this->insert(name, Variable::Qualifier::MUTABLE, location);
	}


	// size of all stacked scopes combined
	std::uint64_t ltn::c::compile::Scope::recSize() const {
		if(this->parent) {
			return this->vars.size() + parent->recSize();
		}
		return this->vars.size();
	}


	const ltn::c::ast::Namespace & ltn::c::compile::Scope::get_namespace() const {
		return this->namespaze;
	}

}

