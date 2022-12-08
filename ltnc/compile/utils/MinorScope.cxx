#include "MinorScope.hxx"

namespace ltn::c {

	MinorScope::MinorScope(const Scope * parent) 
		: parent { parent } {}



	const Variable * MinorScope::resolve(
		const std::string & name,
		const SourceLocation & location) const{
		
		if(this->vars.contains(name)) {
			return &this->vars.at(name);
		}
		else return this->parent->resolve(name, location);
	}



	const type::Type * MinorScope::resolve_type(const std::string & name) const {
		if(this->type_map.contains(name)) {
			return &this->type_map.at(name);
		}
		return this->parent->resolve_type(name);
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



	void MinorScope::override_return_type(type::Type return_type) {
		this->return_type = return_type;
	}


	
	const type::Type & MinorScope::get_return_type() const {
		if(this->return_type) return *this->return_type;
		return this->parent->get_return_type();
	}
}