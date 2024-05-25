#include "StaticScope.hxx"
#include "ltnc/analyze/error.hxx"

namespace ltn::c {
	StaticScope::StaticScope(stx::reference<const GlobalScope> parent)
		: Scope {}
		, parent { parent } {}



	std::uint64_t StaticScope::size() const {
		return 0;
	}



	bool StaticScope::is_const() const {
		return true;
	}



	bool StaticScope::is_coroutine() const {
		return false;
	}



	const Namespace & StaticScope::get_namespace() const {
		return parent->get_namespace();
	}



	std::optional<std::string> StaticScope::get_return() const {
		return parent->get_return();

	}



	Context & StaticScope::get_context() const {
		return parent->get_context();
	}


	
	LocalVariableInfo StaticScope::declare_local_variable(const std::string & name, const SourceLocation & location) {
		throw CompilerError { "Cannot declare a local variable inside the initialization a definition or global variable", location };
	}



	stx::optref<const LocalVariableInfo> StaticScope::resolve_local_variable(const std::string & name, const SourceLocation & location) const {
		return stx::nullref;
	}



	std::uint64_t StaticScope::resolve_member_id(const std::string & name) const {
		return parent->resolve_member_id(name);
	}



	sst::expr_ptr StaticScope::resolve_custom_literal(const std::string & type, const std::string & value) const {
		return parent->resolve_custom_literal(type, value);
	}
}