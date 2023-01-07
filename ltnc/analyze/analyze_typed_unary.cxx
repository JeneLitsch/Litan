#include "analyze.hxx"
#include "ltnc/compile/cast_static.hxx"
// #include "ltnc/compile/cast_dynamic.hxx"
#include "ltnc/compile/copy_static.hxx"
#include "ltnc/compile/copy_dynamic.hxx"

namespace ltn::c {
	namespace {
		type::Type deduce_type(sst::TypedUnary::Op op, const type::Type & target_type) {
			switch (op) {
			case sst::TypedUnary::Op::STATIC_COPY:  return type::deduce_copy_static(target_type);
			case sst::TypedUnary::Op::DYNAMIC_COPY: return type::deduce_copy_dynamic(target_type);
			case sst::TypedUnary::Op::STATIC_CAST:  return type::deduce_cast_static(target_type);
			case sst::TypedUnary::Op::DYNAMIC_CAST: return type::deduce_cast_dynamic(target_type);
			default: throw std::runtime_error{"Invalid TypedUnary::Op"};
			}
		}
	}



	sst::expr_ptr analyze_expr(
		const ast::TypedUnary & tunary,
		Context & context,
		Scope & scope) {
		auto expr = analyze_expression(*tunary.expr, context, scope);
		const auto target_type = instantiate_type(tunary.type, scope);
		const auto op = static_cast<sst::TypedUnary::Op>(tunary.op);
		const auto type = deduce_type(op, target_type);
		return std::make_unique<sst::TypedUnary>(op, target_type, std::move(expr), type);
	}
}