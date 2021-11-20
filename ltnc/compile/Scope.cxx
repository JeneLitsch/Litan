#include "Scope.hxx"
#include "ltnc/CompilerError.hxx"

ltn::c::compile::Scope::Scope(const Scope * parent) 
	: parent(parent) {}

std::uint64_t ltn::c::compile::Scope::resolve(
	const std::string & name,
	std::size_t line) const{
	
	if(this->vars.contains(name)) {
		return this->vars.at(name);
	}
	throw CompilerError{"Undefined variable " + name, line};
}

std::uint64_t ltn::c::compile::Scope::insert(
	const std::string & name,
	std::size_t line) {
	if(this->vars.contains(name)) {
		throw CompilerError{"Redefintion of variable " + name, line};
	}
	const auto addr = recSize();
	this->vars.emplace(name, addr);
	return addr;
}

std::uint64_t ltn::c::compile::Scope::recSize() const {
	if(this->parent) {
		return this->vars.size() + parent->recSize();
	}
	return this->vars.size();
}
