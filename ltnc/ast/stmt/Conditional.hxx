#pragma once
#include "Statement.hxx"
#include "ltnc/ast/util/Conditional.hxx"

namespace ltn::c::ast::stmt {
    struct Conditional : ast::Conditional<Statement> {
		Conditional(const SourceLocation & location);
		virtual void accept(const StmtVisitor & visitor) const override;
    };
    
    std::unique_ptr<Conditional> conditional(const SourceLocation & location);
}