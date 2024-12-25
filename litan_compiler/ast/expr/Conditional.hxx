#pragma once
#include "Expression.hxx"
#include "litan_compiler/ast/util/Conditional.hxx"

namespace ltn::c::ast::expr {
    struct Conditional : ast::Conditional<Expression> {
		Conditional(const SourceLocation & location);
		virtual void accept(const ExprVisitor & visitor) const override;
    };
    
    std::unique_ptr<Conditional> conditional(const SourceLocation & location);
}