#pragma once
#include "Scope.hxx"

namespace ltn::c {
	// Major Scope for e.g. functions 
	class MajorScope final : public Scope {
	public:
		MajorScope(const ast::Namespace & namespaze, bool c0nst);

		virtual Variable resolve(const std::string & name, const SourceLocation & location) const override;
		virtual std::uint64_t size() const override;
		virtual bool is_const() const override;
		virtual const ast::Namespace & get_namespace() const override;
		virtual std::optional<std::string> get_return() const override;
	
	private:
		const ast::Namespace & namespaze;
		bool c0nst = false;
	};
}