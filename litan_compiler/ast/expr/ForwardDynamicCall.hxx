#pragma once
#include "Expression.hxx"

namespace ltn::c::ast::expr {
	struct ForwardDynamicCall final : public Expression {
		ForwardDynamicCall(
			std::uint64_t address,
			std::uint64_t arity,
			const SourceLocation & location);

		void accept(const ExprVisitor & visitor) const;

		std::uint64_t address;
		std::uint64_t arity;
	};

	std::unique_ptr<ForwardDynamicCall> forward_dynamic_call(
		const SourceLocation & location,
		std::uint64_t address,
		std::uint64_t arity
	);
}