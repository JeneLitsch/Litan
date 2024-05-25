#include "MinorScope.hxx"

namespace ltn::c {

	MinorScope::MinorScope(const Scope * parent) 
		: parent { parent } {}




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




	stx::optref<const LocalVariableInfo> MinorScope::resolve_local_variable(
		const std::string & name,
		const SourceLocation & location) const{
		
		if(this->vars.contains(name)) {
			return this->vars.at(name);
		}
		else return this->parent->resolve_local_variable(name, location);
	}



	stx::optref<const ast::decl::Function> MinorScope::resolve_function(
		const std::string & name,
		const Namespace & ns,
		std::size_t arity,
		VariadicMode var_mode) const {

		return this->parent->resolve_function(name, ns, arity, var_mode);
	}



	stx::optref<const sst::decl::Global> MinorScope::resolve_global_variable(
		const std::string & name,
		const Namespace & ns) const {
		
		return this->parent->resolve_global_variable(name, ns);
	}



	stx::optref<const sst::decl::Definition> MinorScope::resolve_definiton(
		const std::string & name,
		const Namespace & ns) const {

		return this->parent->resolve_definiton(name, ns);
	}



	std::uint64_t MinorScope::resolve_member_id(const std::string & name) const {
		return this->parent->resolve_member_id(name);
	}



	sst::expr_ptr MinorScope::resolve_custom_literal(const std::string & type, const std::string & value) const {
		return this->parent->resolve_custom_literal(type, value);
	}
}