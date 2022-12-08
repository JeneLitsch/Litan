#pragma once
#include "Scope.hxx"

namespace ltn::c {
	// Major Scope for e.g. functions 
	class MajorScope : public Scope {
	public:
		MajorScope(const ast::Namespace & namespaze, bool c0nst);

		virtual const Variable * resolve(const std::string & name, const SourceLocation & location) const override;
		virtual std::uint64_t size() const override;
		virtual bool is_const() const override;
		virtual const ast::Namespace & get_namespace() const override;
		virtual std::optional<std::string> get_return() const override;
		virtual const type::Type & get_return_type() const override;
		virtual const type::Type * resolve_type(const std::string & name) const override;

		void set_return_type(type::Type type);
	
	private:
		ast::Namespace namespaze;
		bool c0nst = false;
		type::Type return_type;
	};
}