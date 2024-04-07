#include "Conditional.hxx"

namespace ltn::c::ast::expr {
    Conditional::Conditional(const SourceLocation & location) 
        : ast::Conditional<Expression>{location} {}



    void Conditional::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}



    std::unique_ptr<Conditional> conditional(const SourceLocation & location) {
        return std::make_unique<Conditional>(location);
    }
}