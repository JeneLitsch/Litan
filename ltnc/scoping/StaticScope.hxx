#pragma once
#include "GlobalScope.hxx"

namespace ltn::c {
	class StaticScope : public Scope {
	public:
		StaticScope(stx::reference<const GlobalScope> parent);
		virtual std::uint64_t size() const override;
		virtual bool is_const() const override;
		virtual bool is_coroutine() const override;
		virtual const Namespace & get_namespace() const override;
		virtual std::optional<std::string> get_return() const override;
		virtual Context & get_context() const override;
		
		virtual LocalVariableInfo declare_local_variable(const std::string & name, const SourceLocation & location) override;
		virtual stx::optref<const LocalVariableInfo> resolve_local_variable(const std::string & name, const SourceLocation & location) const override;

		virtual std::uint64_t resolve_member_id(const std::string & name) const override;
		virtual sst::expr_ptr resolve_custom_literal(const std::string & type, const std::string & value) const override;
	
	protected:
		stx::reference<const GlobalScope> parent;
	};
}