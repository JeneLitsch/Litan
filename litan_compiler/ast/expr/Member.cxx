#include "Member.hxx"

namespace ltn::c::ast::expr {
	Member::Member(expr_ptr expr, const std::string & name, const SourceLocation & location)
		: Expression(location)
		, expr(std::move(expr))
		, name(std::move(name)) {};



	void Member::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}



	std::unique_ptr<Member> member(const SourceLocation & location, expr_ptr expr, std::string && name) {
		return std::make_unique<Member>(std::move(expr), name, location);
	}



	std::unique_ptr<Member> member(const SourceLocation & location, expr_ptr expr, const std::string & name) {
		return std::make_unique<Member>(std::move(expr), name, location);
	}
}