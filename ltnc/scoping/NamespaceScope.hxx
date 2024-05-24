#pragma once
#include "Scope.hxx"
#include "ltnc/Namespace.hxx"
#include "GlobalScope.hxx"

namespace ltn::c {
	class NamespaceScope : public Scope {
	public:
		NamespaceScope(const GlobalScope & global_scope, const Namespace & namespaze);
		
		virtual std::uint64_t size() const override;
		virtual bool is_const() const override;
		virtual bool is_coroutine() const override;
		virtual const Namespace & get_namespace() const override;
		virtual std::optional<std::string> get_return() const override;
		virtual Context & get_context() const override;
		
		virtual Variable declare_variable(const std::string & name, const SourceLocation & location) override;
		virtual stx::optref<const Variable> resolve_local_variable(const std::string & name, const SourceLocation & location) const override;
	
	private:
		stx::reference<const GlobalScope> global_scope;
		Namespace namespaze;
	};
}
