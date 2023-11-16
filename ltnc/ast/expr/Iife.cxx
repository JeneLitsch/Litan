#include "Expression.hxx"
#include "ltnc/ast/stmt/Statement.hxx"

namespace ltn::c::ast::expr {
	Iife::Iife(
		const SourceLocation & location,
		stmt_ptr stmt) 
		: Expression(location)
		, stmt(std::move(stmt)) {}
		


	void Iife::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}

	Iife::~Iife() {}
}