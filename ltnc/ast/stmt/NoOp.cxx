#include "NoOp.hxx"

namespace ltn::c::ast::stmt {
	NoOp::NoOp(const SourceLocation & location) : Statement(location) {}

	void NoOp::accept(
		
		const StmtVisitor & visitor) const{
		visitor.visit(*this);
	}



	std::unique_ptr<NoOp> no_op(const SourceLocation & location) {
		return std::make_unique<NoOp>(location);
	}
}