#pragma once
#include <map>
#include "MinorScope.hxx"

namespace ltn::c {
	// Major Scope for e.g. functions 
	class CaseScope final : public MinorScope {
	public:
		CaseScope(const Scope * outer);

		virtual stx::optref<const ast::decl::Function> resolve_function(const std::string & name, const Namespace & ns, std::size_t arity, VariadicMode var_mode = VariadicMode::PROHIBITED) const override;
		virtual stx::optref<const sst::decl::Global> resolve_global_variable(const std::string & name, const Namespace & ns) const override;

	private:
		mutable InvalidFunctionTable fx_table {"case"};
		mutable InvalidGlobalTable global_table {"case"};
	};
}