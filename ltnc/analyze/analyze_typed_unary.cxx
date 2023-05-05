// #include "analyze.hxx"
// #include "ltnc/type/traits.hxx"

// namespace ltn::c {
// 	namespace {
// 		using Op = ast::TypedUnary::Op;
// 		type::Type deduce_type(Op op, const type::Type & target_type) {
// 			switch (op) {
// 			case Op::STATIC_CAST:  return type::deduce_cast_static(target_type);
// 			case Op::DYNAMIC_CAST: return type::deduce_cast_dynamic(target_type);
// 			case Op::FORCE_CAST:   return type::deduce_cast_force(target_type);
// 			case Op::STATIC_COPY:  return type::deduce_copy_static(target_type);
// 			case Op::DYNAMIC_COPY: return type::deduce_copy_dynamic(target_type);
// 			case Op::FORCE_COPY:   return type::deduce_copy_force(target_type);
// 			default: throw std::runtime_error{"Invalid TypedUnary::Op"};
// 			}
// 		}



// 		bool is_castable(Op op, const type::Type & from, const type::Type & to) {
// 			switch (op) {
// 			case Op::STATIC_CAST:  return type::is_static_castable(from, to);
// 			case Op::DYNAMIC_CAST: return type::is_dynamic_castable(to);
// 			case Op::FORCE_CAST:   return type::is_force_castable(to);
// 			case Op::STATIC_COPY:  return type::is_static_copyable(from, to);
// 			case Op::DYNAMIC_COPY: return type::is_dynamic_copyable(to);
// 			case Op::FORCE_COPY:   return type::is_force_copyable(to);
// 			default: throw std::runtime_error{"Invalid TypedUnary::Op"};
// 			}
// 		}
// 	}



// 	sst::expr_ptr analyze_expr(const ast::TypedUnary & tunary, Scope & scope) {
// 		auto expr = analyze_expression(*tunary.expr, scope);
// 		const auto target_type = analyze_type(*tunary.type, scope);
// 		const auto op = tunary.op;
// 		const auto type = deduce_type(op, target_type);
// 		if(!is_castable(op, expr->type, target_type)) {
// 			throw cannot_cast(location(tunary), expr->type, target_type);
// 		}
// 		return std::make_unique<sst::TypedUnary>(op, target_type, std::move(expr), type);
// 	}
// }