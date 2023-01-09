#include "analyze.hxx"
#include "ltnc/type/check.hxx"
#include "ltnc/compile/cast_static.hxx"
// #include "ltnc/compile/cast_dynamic.hxx"
#include "ltnc/compile/copy_static.hxx"
#include "ltnc/compile/copy_dynamic.hxx"

namespace ltn::c {
	namespace {
		bool is_static_castable(const type::Type & from, const type::Type & to) {
			if(type::is_any(to))  return true;
			if(type::is_bool(to)) return true;
			if(type::is_numeric(from) && type::is_char(to)) return true;
			if(type::is_numeric(from) && type::is_int(to)) return true;
			if(type::is_numeric(from) && type::is_float(to)) return true;
			if(type::is_empty_array(from) && type::is_array(to)) return true;
			return false;
		}



		bool is_dynamic_castable(const type::Type & from, const type::Type & to) {
			if(type::is_any(to))    return true;
			if(type::is_bool(to))   return true;
			if(type::is_char(to))   return true;
			if(type::is_int(to))    return true;
			if(type::is_float(to))  return true;
			if(type::is_string(to)) return true;
			if(type::is_array(to)) {
				return is_dynamic_castable(from, **to.as<type::Array>()->contains);
			}
			return false;
		}






		bool is_static_copyable(const type::Type & from, const type::Type & to) {
			if(type::is_bool(to)) return true;
			if(type::is_numeric(from) && type::is_char(to)) return true;
			if(type::is_numeric(from) && type::is_int(to)) return true;
			if(type::is_numeric(from) && type::is_float(to)) return true;
			if(type::is_numeric_array(from) && type::is_string(to)) return true;
			if(type::is_empty_array(from) && type::is_string(to)) return true;
			if(type::is_string(from) && type::is_string(to)) return true;
			if(type::is_string(from) && type::is_numeric_array(to)) return true;
			if(type::is_empty_array(from) && type::is_array(to)) return true;
			if(type::is_array(from) && type::is_empty_array(to)) return false;
			if(type::is_array(from) && type::is_array(to)) {
				return is_dynamic_castable(
					**from.as<type::Array>()->contains,
					**to.as<type::Array>()->contains
				);
			}
			return false;
		}



		bool is_dynamic_copyable(const type::Type & from, const type::Type & to) {
			if(type::is_any(to))    return true;
			if(type::is_bool(to))   return true;
			if(type::is_char(to))   return true;
			if(type::is_int(to))    return true;
			if(type::is_float(to))  return true;
			if(type::is_string(to)) return true;
			if(type::is_array(to)) {
				return is_dynamic_copyable(from, **to.as<type::Array>()->contains);
			}
			return false;
		}



		type::Type deduce_type(sst::TypedUnary::Op op, const type::Type & target_type) {
			using Op = sst::TypedUnary::Op;
			switch (op) {
			case Op::STATIC_COPY:  return type::deduce_copy_static(target_type);
			case Op::DYNAMIC_COPY: return type::deduce_copy_dynamic(target_type);
			case Op::STATIC_CAST:  return type::deduce_cast_static(target_type);
			case Op::DYNAMIC_CAST: return type::deduce_cast_dynamic(target_type);
			default: throw std::runtime_error{"Invalid TypedUnary::Op"};
			}
		}



		bool is_castable(sst::TypedUnary::Op op, const type::Type & from, const type::Type & to) {
			using Op = sst::TypedUnary::Op;
			switch (op) {
			case Op::STATIC_COPY:  return is_static_copyable(from, to);
			case Op::DYNAMIC_COPY: return is_dynamic_copyable(from, to);
			case Op::STATIC_CAST:  return is_static_castable(from, to);
			case Op::DYNAMIC_CAST: return is_dynamic_castable(from, to);
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
		const auto op = static_cast<sst::TypedUnary::Op>(tunary.op);
		const auto type = deduce_type(op, target_type);
		if(is_castable(op, expr->type, target_type)) {
			return std::make_unique<sst::TypedUnary>(op, target_type, std::move(expr), type);
		}
		else {
			throw cannot_cast(expr->type, target_type, tunary.location);
		}
	}
}