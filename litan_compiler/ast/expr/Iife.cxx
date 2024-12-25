#include "Iife.hxx"
#include "litan_compiler/ast/stmt/Statement.hxx"

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



	std::unique_ptr<Iife> iife(const SourceLocation & location, stmt_ptr stmt) {
		return std::make_unique<Iife>(location, std::move(stmt));
	}
}