#pragma once
#include <map>
#include "LocalScope.hxx"
#include "NamespaceScope.hxx"

namespace ltn::c {
	// Major Scope for e.g. functions 
	class FunctionScope final : public LocalScope {
	public:
		FunctionScope(const NamespaceScope & namspace_scope, Qualifiers qualifiers);

		virtual std::uint64_t size() const override;
		virtual bool is_const() const override;
		virtual bool is_coroutine() const override;
		virtual const Namespace & get_namespace() const override;
		virtual std::optional<std::string> get_return() const override;
		virtual Context & get_context() const override;

		virtual stx::optref<const LocalVariableInfo> resolve_local_variable(const std::string & name, const SourceLocation & location) const override;
		virtual stx::optref<const ast::decl::Function> resolve_function(const std::string & name, const Namespace & ns, std::size_t arity, VariadicMode var_mode = VariadicMode::PROHIBITED) const override;
		virtual stx::optref<const sst::decl::Global> resolve_global_variable(const std::string & name, const Namespace & ns) const override;
		virtual stx::optref<const sst::decl::Definition> resolve_definiton(const std::string & name, const Namespace & ns) const override;
		virtual std::uint64_t resolve_member_id(const std::variant<std::string, MemberCode> & name) const override;
		virtual sst::expr_ptr resolve_custom_literal(const std::string & type, const std::string & value) const override;
	private:
		stx::reference<const NamespaceScope> namspace_scope;
		Qualifiers qualifiers;
	};
}