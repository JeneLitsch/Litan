#pragma once
#include "GlobalScope.hxx"
#include "ltnc/Namespace.hxx"
#include "RootScope.hxx"

namespace ltn::c {
	class NamespaceScope : public GlobalScope {
	public:
		NamespaceScope(stx::reference<const GlobalScope> parent, const Namespace & namespaze);
		
		virtual std::uint64_t size() const override;
		virtual bool is_const() const override;
		virtual bool is_coroutine() const override;
		virtual const Namespace & get_namespace() const override;
		virtual std::optional<std::string> get_return() const override;
		virtual Context & get_context() const override;
		
		virtual LocalVariableInfo declare_local_variable(const std::string & name, const SourceLocation & location) override;

		virtual stx::optref<const LocalVariableInfo> resolve_local_variable(const std::string & name, const SourceLocation & location) const override;
		virtual stx::optref<const ast::decl::Function> resolve_function(const std::string & name, const Namespace & ns, std::size_t arity, VariadicMode var_mode = VariadicMode::PROHIBITED) const override;
		virtual stx::optref<const sst::decl::Global> resolve_global_variable(const std::string & name, const Namespace & ns) const override;
		virtual stx::optref<const sst::decl::Definition> resolve_definiton(const std::string & name, const Namespace & ns) const override;
		virtual std::uint64_t resolve_member_id(const std::string & name) const override;
		virtual sst::expr_ptr resolve_custom_literal(const std::string & type, const std::string & value) const override;

		NamespaceScope & add_namespace(const Namespace & ns);
		const std::string & get_namespace_name() const;

	private:
		stx::reference<const GlobalScope> parent;
		Namespace namespaze;
		std::vector<std::unique_ptr<NamespaceScope>> children;
	};
}
