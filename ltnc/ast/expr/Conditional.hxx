#pragma once
#include "Expression.hxx"
#include "ltnc/ast/util/Conditional.hxx"

namespace ltn::c::ast::expr {
    struct Conditional : ast::Conditional<Expression> {
		Conditional(const SourceLocation & location);
		virtual void accept(const ExprVisitor & visitor) const override;
        void add_case(expr_ptr cond, expr_ptr body);
        void set_else(expr_ptr body);
    };
    
    std::unique_ptr<Conditional> conditional(const SourceLocation & location);
}