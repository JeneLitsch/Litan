#include "GlobalScope.hxx"

namespace ltn::c {
	GlobalScope::GlobalScope(stx::reference<Context> context)
		: Scope {}
		, context { context } {}



	std::uint64_t GlobalScope::size() const {
		return 0;
	}



	bool GlobalScope::is_const() const {
		return true;
	}



	bool GlobalScope::is_coroutine() const {
		return false;
	}
	
	

	const Namespace & GlobalScope::get_namespace() const {
		return {};
	}
	
	
	
	std::optional<std::string> GlobalScope::get_return() const {
		return std::nullopt;
	}
	
	

	Context & GlobalScope::get_context() const {
		return context;
	}
	

	
	void GlobalScope::set_return(const std::string & return_point) {
		// TODO ERROR
	}



	Variable GlobalScope::declare_variable(const std::string & name, const SourceLocation & location) {
		// TODO ERROR
		throw "";
	}



	stx::optref<const Variable> GlobalScope::resolve_local_variable(const std::string & name, const SourceLocation & location) const {
		return stx::nullref;
	}
}