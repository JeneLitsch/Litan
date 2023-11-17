#pragma once
#include "ForwardDynamicCall.hxx"

namespace ltn::c::ast::expr {
	ForwardDynamicCall::ForwardDynamicCall(
		std::uint64_t address,
		std::uint64_t arity,
		const SourceLocation & location)
		: Expression(location)
		, address{address}
		, arity{arity} {}



	void ForwardDynamicCall::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}



	std::unique_ptr<ForwardDynamicCall> forward_dynamic_call(
		const SourceLocation & location,
		std::uint64_t address,
		std::uint64_t arity) {

		return std::make_unique<ForwardDynamicCall>(address, arity, location);
	}
}