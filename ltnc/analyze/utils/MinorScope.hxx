#pragma once
#include "Scope.hxx"

namespace ltn::c {
	class MinorScope final : public Scope {
	public:
		MinorScope(const Scope * parent);

		virtual const Variable * resolve(const std::string & name, const SourceLocation & location) const override;
		virtual std::uint64_t size() const override;
		virtual bool is_const() const override;
		virtual const Namespace & get_namespace() const override;
		virtual std::optional<std::string> get_return() const override;
		virtual const type::Type & get_return_type() const override;
		virtual const type::Type * resolve_type(const std::string & name) const override;


		void override_return_type(type::Type return_type);

	private:
		const Scope * parent;
		std::optional<type::Type> return_type;
	};
}