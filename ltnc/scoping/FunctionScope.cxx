#include "FunctionScope.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	FunctionScope::FunctionScope(
		const NamespaceScope & namspace_scope,
		Qualifiers qualifiers)
		: LocalScope {}
		, namspace_scope { namspace_scope }
		, qualifiers { qualifiers } {}



	bool FunctionScope::is_const() const {
		return this->qualifiers.is_const;
	}



	bool FunctionScope::is_coroutine() const {
		return this->qualifiers.is_coroutine;
	}



	const Namespace & FunctionScope::get_namespace() const {
		return this->namspace_scope->get_namespace();
	}



	std::uint64_t FunctionScope::size() const {
		return this->vars.size();
	}



	std::optional<std::string> FunctionScope::get_return() const {
		return this->return_point;
	}


	Context & FunctionScope::get_context() const {
		return this->namspace_scope->get_context();
	}

	

	stx::optref<const LocalVariableInfo> FunctionScope::resolve_local_variable(
		const std::string & name,
		const SourceLocation &) const{
		
		if(this->vars.contains(name)) {
			return this->vars.at(name);
		}
		return stx::nullref;
	}



	stx::optref<const ast::decl::Function> FunctionScope::resolve_function(
		const std::string & name,
		const Namespace & ns,
		std::size_t arity,
		VariadicMode var_mode) const {

		return namspace_scope->resolve_function(name, ns, arity, var_mode);
	}



	stx::optref<const sst::decl::Global> FunctionScope::resolve_global_variable(
		const std::string & name,
		const Namespace & ns) const {
		
		return namspace_scope->resolve_global_variable(name, ns);
	}



	stx::optref<const sst::decl::Definition> FunctionScope::resolve_definiton(
		const std::string & name,
		const Namespace & ns) const {

		return namspace_scope->resolve_definiton(name, ns);
	}



	std::uint64_t FunctionScope::resolve_member_id(const std::string & name) const {
		return namspace_scope->resolve_member_id(name);
	}



	sst::expr_ptr FunctionScope::resolve_custom_literal(const std::string & type, const std::string & value) const {
		return namspace_scope->resolve_custom_literal(type, value);
	}
}