#include "Conditional.hxx"

namespace ltn::c::ast::expr {
    Conditional::Conditional(const SourceLocation & location) 
        : ast::Conditional<Expression>{location} {}



    void Conditional::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}



    void Conditional::add_case(expr_ptr cond, expr_ptr body) {
        this->cases.push_back(std::make_tuple(std::move(cond), std::move(body)));
    }



    void Conditional::set_else(expr_ptr body) {
        this->else_branch = std::move(body);
    }


    
    std::unique_ptr<Conditional> conditional(const SourceLocation & location) {
        return std::make_unique<Conditional>(location);
    }
}