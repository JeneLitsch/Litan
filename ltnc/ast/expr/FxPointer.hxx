#pragma once
#include "Expression.hxx"

namespace ltn::c::ast::expr {
	struct FxPointer final : public Expression {
		FxPointer(
			const std::string & name,
			const Namespace & namespaze,
			std::uint64_t placeholders,
			bool is_variadic,
			const SourceLocation & location);
		
		virtual void accept(const ExprVisitor & visitor) const override;
		std::uint64_t arity() const;

		std::string name;
		Namespace namespaze;
		std::uint64_t placeholders;
		bool is_variadic;
	};

	std::unique_ptr<FxPointer> fx_pointer(
		const SourceLocation & location, 
		const std::string & name,
		const Namespace & namespaze,
		std::uint64_t placeholders,
		bool is_variadic
	);
}