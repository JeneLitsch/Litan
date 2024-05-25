#include "DefinitionScope.hxx"

namespace ltn::c {
	DefinitionScope::DefinitionScope(stx::reference<const GlobalScope> parent)
		: StaticScope { parent }
		{}
	
	
	
	stx::optref<const ast::decl::Function> DefinitionScope::resolve_function(const std::string & name, const Namespace & ns, std::size_t arity, VariadicMode var_mode) const {
		return stx::nullref;
	}



	stx::optref<const sst::decl::Global> DefinitionScope::resolve_global_variable(const std::string & name, const Namespace & ns) const {
		return stx::nullref;
	}



	stx::optref<const sst::decl::Definition> DefinitionScope::resolve_definiton(const std::string & name, const Namespace & ns) const {
		return stx::nullref;
	}
}