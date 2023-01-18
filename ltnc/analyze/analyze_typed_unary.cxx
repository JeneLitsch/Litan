#include "analyze.hxx"
#include "ltnc/type/traits.hxx"

namespace ltn::c {
	namespace {
		type::Type deduce_type(ast::TypedUnary::Op op, const type::Type & target_type) {
			using Op = ast::TypedUnary::Op;
			switch (op) {
			case Op::STATIC_CAST:  return type::deduce_cast_static(target_type);
			case Op::DYNAMIC_CAST: return type::deduce_cast_dynamic(target_type);
			case Op::FORCE_CAST:   return type::Error{};
			case Op::STATIC_COPY:  return type::deduce_copy_static(target_type);
			case Op::DYNAMIC_COPY: return type::deduce_copy_dynamic(target_type);
			default: throw std::runtime_error{"Invalid TypedUnary::Op"};
			}
		}



		bool is_castable(ast::TypedUnary::Op op, const type::Type & from, const type::Type & to) {
			using Op = ast::TypedUnary::Op;
			switch (op) {
			case Op::STATIC_CAST:  return type::is_static_castable(from, to);
			case Op::DYNAMIC_CAST: return type::is_dynamic_castable(to);
			case Op::FORCE_CAST:   return false;
			case Op::STATIC_COPY:  return type::is_static_copyable(from, to);
			case Op::DYNAMIC_COPY: return type::is_dynamic_copyable(to);
			default: throw std::runtime_error{"Invalid TypedUnary::Op"};
			}
		}



		CompilerError cannot_cast(
			const type::Type & from,
			const type::Type & to,
			const SourceLocation & location) {
		
			std::ostringstream oss;
			oss << "Cannot cast " << from << " to " << to;
			return CompilerError{oss.str(), location};
		}
	}



	sst::expr_ptr analyze_expr(
		const ast::TypedUnary & tunary,
		Context & context,
		Scope & scope) {
		auto expr = analyze_expression(*tunary.expr, context, scope);
		const auto target_type = instantiate_type(tunary.type, scope);
		const auto op = tunary.op;
		const auto type = deduce_type(op, target_type);
		if(!is_castable(op, expr->type, target_type)) {
			throw cannot_cast(expr->type, target_type, tunary.location);
		}
		return std::make_unique<sst::TypedUnary>(op, target_type, std::move(expr), type);
	}
}