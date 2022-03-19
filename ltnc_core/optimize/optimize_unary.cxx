#include "optimize.hxx"
#include "ltn/casts.hxx"
namespace ltn::c::optimize {
	bool is_negation(const ast::Unary & unary) {
		return unary.type == ast::Unary::Type::NEG;
	}
	
	
	ast::expr_ptr unary(std::unique_ptr<ast::Unary> unary) {
		auto & inner = unary->expression;
		inner = expression(std::move(inner));
		if(check_unique<ast::Integer>(inner) && is_negation(*unary)) {
			auto integer = unique_cast<ast::Integer>(std::move(inner));
			integer->value = -integer->value;
			return integer;
		}
		return unary;
	}
}