#pragma once
#include "Scope.hxx"

namespace ltn::c {
	class MinorScope final : public Scope {
	public:
		MinorScope(const Scope * parent);

		virtual stx::optref<const Variable> resolve_variable(const std::string & name, const SourceLocation & location) const override;
		virtual std::uint64_t size() const override;
		virtual bool is_const() const override;
		virtual bool is_coroutine() const override;
		virtual const Namespace & get_namespace() const override;
		virtual std::optional<std::string> get_return() const override;
		virtual Context & get_context() const override;
		virtual void set_context(stx::reference<Context> context) override;

	private:
		const Scope * parent;
		stx::optref<Context> context = stx::nullref;
	};
}