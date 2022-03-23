#include "optimize.hxx"
#include "ltn/casts.hxx"
namespace ltn::c::optimize {
	// namespace {
	// 	template<ast::Binary::Type op>
	// 	bool is_op_type(const ast::Binary & binary) {
	// 		return binary.type == op;
	// 	}
	// 	constexpr auto is_add = is_op_type<ast::Binary::Type::ADD>
	// }



	// template<typename Operator, typename LitrL, typename LitrR>
	// ast::expr_ptr eval(ast::Expression & expr_l, ast::Expression & expr_r) {
	// 	static constexpr Operator op;
	// 	auto * l = as<LitrL>(expr_l);
	// 	auto * r = as<LitrL>(expr_r);
	// 	if(l && r) {
	// 		return op();
	// 	}
	// 	return nullptr;
	// }



	ast::expr_ptr binary(ast::Binary & expr) {
		auto & l = expr.l;
		auto & r = expr.r;
		l = expression(std::move(l));
		r = expression(std::move(r));
		return nullptr;
	}
}