#include "CaseScope.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	CaseScope::CaseScope(const Scope * outer) 
		: MinorScope { outer } {}



	stx::optref<const ast::decl::Function> CaseScope::resolve_function(const std::string & name, const Namespace & ns, std::size_t arity, VariadicMode var_mode) const {
		return stx::to_optref(this->fx_table.resolve(name, this->get_namespace(), ns, arity, var_mode));
	}

	
	
	stx::optref<const sst::decl::Global> CaseScope::resolve_global_variable(const std::string & name, const Namespace & ns) const {
		return stx::to_optref(this->global_table.resolve(name, ns));
	}
}