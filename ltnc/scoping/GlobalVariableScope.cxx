#include "GlobalVariableScope.hxx"

namespace ltn::c {
	GlobalVariableScope::GlobalVariableScope(stx::reference<const GlobalScope> parent)
		: StaticScope { parent }
		{}
	
	
	
	stx::optref<const ast::decl::Function> GlobalVariableScope::resolve_function(const std::string & name, const Namespace & ns, std::size_t arity, VariadicMode var_mode) const {
		return stx::nullref;
	}



	stx::optref<const sst::decl::Global> GlobalVariableScope::resolve_global_variable(const std::string & name, const Namespace & ns) const {
		return stx::nullref;
	}



	stx::optref<const sst::decl::Definition> GlobalVariableScope::resolve_definiton(const std::string & name, const Namespace & ns) const {
		return parent->resolve_definiton(name, ns);
	}
}