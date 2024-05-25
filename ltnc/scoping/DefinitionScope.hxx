#pragma once
#include "StaticScope.hxx"

namespace ltn::c {
	class DefinitionScope : public StaticScope {
	public:
		DefinitionScope(stx::reference<const GlobalScope> parent);
		virtual stx::optref<const ast::decl::Function> resolve_function(const std::string & name, const Namespace & ns, std::size_t arity, VariadicMode var_mode = VariadicMode::PROHIBITED) const override;
		virtual stx::optref<const sst::decl::Global> resolve_global_variable(const std::string & name, const Namespace & ns) const override;
		virtual stx::optref<const sst::decl::Definition> resolve_definiton(const std::string & name, const Namespace & ns) const override;
	};
}