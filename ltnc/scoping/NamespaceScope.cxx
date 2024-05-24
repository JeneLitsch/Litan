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
		// TODO ERROR
		throw "";
	}


	stx::optref<const Variable> NamespaceScope::resolve_local_variable(const std::string & name, const SourceLocation & location) const {
		return global_scope->resolve_local_variable(name, location);
	}

}