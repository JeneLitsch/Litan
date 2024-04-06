#pragma once
#include "Expression.hxx"
#include "ltnc/sst/util/Conditional.hxx"

namespace ltn::c::sst::expr {
    struct Conditional : sst::Conditional<Expression> {
		Conditional();
		virtual void accept(const ExprVisitor & visitor) const override;
		virtual std::uint64_t alloc() const override;
    };
    
    std::unique_ptr<Conditional> conditional();
}