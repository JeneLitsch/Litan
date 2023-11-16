#include "Switch.hxx"
#include "ltnc/ast/expr/Expression.hxx"

namespace ltn::c::ast::stmt {
	Switch::Switch(const SourceLocation & location)
		: Statement(location) {}



	void Switch::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}



	std::unique_ptr<Switch> sw1tch(const SourceLocation & location) {
		return std::make_unique<Switch>(location);
	}
}