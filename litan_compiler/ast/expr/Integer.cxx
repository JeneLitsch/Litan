#include "Integer.hxx"

namespace ltn::c::ast::expr {
	Integer::Integer(std::int64_t value, const SourceLocation & location)
		: Expression(location), value(value) {}



	void Integer::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}
	


	std::unique_ptr<Integer> integer(std::int64_t value, const SourceLocation & location) {
		return std::make_unique<Integer>(value, location);
	}



	std::unique_ptr<Integer> integer(std::bitset<64> value, const SourceLocation & location) {
		return integer(static_cast<std::int64_t>(value.to_ullong()), location);
	}
}