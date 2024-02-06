#include "Conditional.hxx"

namespace ltn::c::ast::stmt {
    Conditional::Conditional(const SourceLocation & location) 
        : ast::Conditional<Statement>{location} {}



    void Conditional::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}

    
    std::unique_ptr<Conditional> conditional(const SourceLocation & location) {
        return std::make_unique<Conditional>(location);
    }
}