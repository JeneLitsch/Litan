#include "MinorScope.hxx"

namespace ltn::c {

	MinorScope::MinorScope(const Scope * parent) 
		: parent { parent } {}



	Variable MinorScope::resolve(
		const std::string & name,
		const SourceLocation & location) const{
		
		if(this->vars.contains(name)) {
			return this->vars.at(name);
		}
		else return this->parent->resolve(name, location);
	}



	bool MinorScope::is_const() const {
		return this->parent->is_const();
	}



	const ast::Namespace & MinorScope::get_namespace() const {
		return this->parent->get_namespace();
	}
	


	std::uint64_t MinorScope::size() const {
		return this->vars.size() + parent->size();
	}



	std::optional<std::string> MinorScope::get_return() const {
		if(this->return_point) {
			return this->return_point;
		}
		else if(this->parent) {
			return this->parent->get_return();
		}
		else {
			return std::nullopt;
		}
	}
}