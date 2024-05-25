#include "NamespaceScope.hxx"

namespace ltn::c {
	NamespaceScope::NamespaceScope(const GlobalScope & global_scope, const Namespace & namespaze)
		: Scope {}
		, global_scope { global_scope }
		, namespaze { namespaze } {

	}
	
	
	
	std::uint64_t NamespaceScope::size() const {
		return global_scope->size();
	}



	bool NamespaceScope::is_const() const {
		return global_scope->is_const();
	}



	bool NamespaceScope::is_coroutine() const {
		return global_scope->is_coroutine();
	}



	const Namespace & NamespaceScope::get_namespace() const {
		return namespaze;
	}


	std::optional<std::string> NamespaceScope::get_return() const {
		return global_scope->get_return();
	}



	Context & NamespaceScope::get_context() const {
		return global_scope->get_context();
	}



	Variable NamespaceScope::declare_variable(const std::string & name, const SourceLocation & location) {
		throw std::runtime_error { "Cannot declare local varaible in namespace scope" };
	}


	stx::optref<const Variable> NamespaceScope::resolve_local_variable(const std::string & name, const SourceLocation & location) const {
		return global_scope->resolve_local_variable(name, location);
	}



	stx::optref<const ast::decl::Function> NamespaceScope::resolve_function(
		const std::string & name,
		const Namespace & ns,
		std::size_t arity,
		VariadicMode var_mode) const {

		auto & context = this->get_context();
		auto * fx = context.fx_table.resolve(name, this->get_namespace(), ns, arity, var_mode);
		return stx::to_optref(fx);
	}



	stx::optref<const sst::decl::Global> NamespaceScope::resolve_global_variable(
		const std::string & name,
		const Namespace & ns) const {
		
		auto & context = this->get_context();
		auto * glob = context.global_table.resolve(name, this->get_namespace(), ns);
		return stx::to_optref(glob);
	}



	stx::optref<const sst::decl::Definition> NamespaceScope::resolve_definiton(
		const std::string & name,
		const Namespace & ns) const {

		auto & context = this->get_context();
		auto * def = context.definition_table.resolve(name, this->get_namespace(), ns);
		return stx::to_optref(def);
	}



	std::uint64_t NamespaceScope::resolve_member_id(const std::variant<std::string, MemberCode> & name) const {
		return global_scope->resolve_member_id(name);
	}



	sst::expr_ptr NamespaceScope::resolve_custom_literal(const std::string & type, const std::string & value) const {
		return global_scope->resolve_custom_literal(type, value);
	}
}