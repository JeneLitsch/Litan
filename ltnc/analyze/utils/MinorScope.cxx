#include "MinorScope.hxx"

namespace ltn::c {

	MinorScope::MinorScope(const Scope * parent) 
		: parent { parent } {}



	stx::optref<const Variable> MinorScope::resolve_variable(
		const std::string & name,
		const SourceLocation & location) const{
		
		if(this->vars.contains(name)) {
			return this->vars.at(name);
		}
		else return this->parent->resolve_variable(name, location);
	}



	bool MinorScope::is_const() const {
		return this->parent->is_const();
	}



	bool MinorScope::is_coroutine() const {
		return this->parent->is_coroutine();
	}



	const Namespace & MinorScope::get_namespace() const {
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



	Context & MinorScope::get_context() const {
		if(this->context) return *this->context;
		else return this->parent->get_context();
	}



	void MinorScope::set_context(stx::reference<Context> context) {
		this->context = *context;
	}
}