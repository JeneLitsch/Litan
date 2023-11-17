#include "InvokeMember.hxx"

namespace ltn::c::ast::expr {
	InvokeMember::InvokeMember(
		expr_ptr object,
		const std::variant<std::string, MemberCode> & name,
		std::vector<expr_ptr> arguments,
		const SourceLocation & location)
		: Expression(location)
		, object(std::move(object))
		, name{std::move(name)}
		, arguments(std::move(arguments)) {}



	void InvokeMember::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}



	std::uint64_t InvokeMember::arity() const {
		return std::size(this->arguments);
	}

	

	std::unique_ptr<InvokeMember> invoke_member(
		const SourceLocation & location,
		expr_ptr object,
		const std::variant<std::string, MemberCode> & name,
		std::vector<expr_ptr> arguments) {
		
		return std::make_unique<InvokeMember>(std::move(object), name, std::move(arguments), location);
	}
}