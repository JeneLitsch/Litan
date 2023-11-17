#include "Map.hxx"

namespace ltn::c::ast::expr {
	Map::Map(const SourceLocation & location)
		: Expression{location} {}
		
	void Map::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}


	std::unique_ptr<Map> map(const SourceLocation & location) {
		return std::make_unique<Map>(location);
	}
}