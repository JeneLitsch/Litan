#include "transpile.hxx"

namespace ltn::c {
	std::string transpile_expression(
		const sst::Expression & expr,
		unsigned indentation,
		const lang::Language & lang) {
		
		return sst::visit_expression(expr, [&] (const auto & e) {
			return transpile_expr(e, indentation, lang);
		});
	}



	std::string transpile_expr(
		const sst::Lambda & expr,
		unsigned indentation,
		const lang::Language & lang) {
		return  "/* LAMBDA */";
	}



	std::string transpile_expr(
		const sst::ExprSwitch & expr,
		unsigned indentation,
		const lang::Language & lang) {

		return  "/* CHOOSE */";
	}



	std::string transpile_expr(
		const sst::Ternary & expr,
		unsigned indentation,
		const lang::Language & lang) {

		return  "/* TERNARY */";
	}



	std::string transpile_expr(
		const sst::Binary & expr,
		unsigned indentation,
		const lang::Language & lang) {

		return  "/* BINARY */";
	}



	std::string transpile_expr(
		const sst::Unary & expr,
		unsigned indentation,
		const lang::Language & lang) {

		return  "/* UNARY */";
	}



	std::string transpile_expr(
		const sst::Integer & expr,
		unsigned indentation,
		const lang::Language & lang) {

		std::ostringstream oss;
		oss << expr.value;
		return oss.str();
	}



	std::string transpile_expr(
		const sst::Float & expr,
		unsigned indentation,
		const lang::Language & lang) {
		
		std::ostringstream oss;
		oss << std::showpoint << expr.value;
		return oss.str();
	}



	std::string transpile_expr(
		const sst::Bool & expr,
		unsigned indentation,
		const lang::Language & lang) {

		return std::string(expr.value
			? lang.keyword_true()
			: lang.keyword_false()
		);
	}



	std::string transpile_expr(
		const sst::Char & expr,
		unsigned indentation,
		const lang::Language & lang) {

		return  "/* CHAR */";
	}



	std::string transpile_expr(
		const sst::Null & expr,
		unsigned indentation,
		const lang::Language & lang) {

		return std::string(lang.keyword_null());
	}



	std::string transpile_expr(
		const sst::String & expr,
		unsigned indentation,
		const lang::Language & lang) {

		return  "/* STRING */";
	}



	std::string transpile_expr(
		const sst::Array & expr,
		unsigned indentation,
		const lang::Language & lang) {

		return  "/* ARRAY */";
	}



	std::string transpile_expr(
		const sst::Tuple & expr,
		unsigned indentation,
		const lang::Language & lang) {

		return  "/* TUPLE */";
	}



	std::string transpile_expr(
		const sst::Call & call,
		unsigned indentation,
		const lang::Language & lang) {

		std::ostringstream oss;
		oss << call.label.mangle() << "(";
		bool start = true;
		for(const auto & arg : call.parameters) {
			if(start) {
				start = false;
			}
			else {
				oss << lang.call_args_separation();
			}
			oss << transpile_expression(*arg, indentation, lang);
		}
		oss << ")";

		return oss.str();
	}



	std::string transpile_expr(
		const sst::Invoke & expr,
		unsigned indentation,
		const lang::Language & lang) {

		return  "/* INVOKE */";
	}



	std::string transpile_expr(
		const sst::Index & expr,
		unsigned indentation,
		const lang::Language & lang) {

		return  "/* INDEX */";
	}



	std::string transpile_expr(
		const sst::FxPointer & expr,
		unsigned indentation,
		const lang::Language & lang) {

		return  "/* FX_PTR */";
	}



	std::string transpile_expr(
		const sst::Iife & expr,
		unsigned indentation,
		const lang::Language & lang) {

		return  "/* IIFE */";
	}



	std::string transpile_expr(
		const sst::Var & expr,
		unsigned indentation,
		const lang::Language & lang) {

		return  "/* EXPRVAR */";
	}



	std::string transpile_expr(
		const sst::Member & expr,
		unsigned indentation,
		const lang::Language & lang) {

		return  "/* EXPRMEMBER */";
	}



	std::string transpile_expr(
		const sst::GlobalVar & expr,
		unsigned indentation,
		const lang::Language & lang) {

		return  "/* EXPRGLOBAL */";
	}



	std::string transpile_expr(
		const sst::TypedUnary & expr,
		unsigned indentation,
		const lang::Language & lang) {

		return  "/* TYPED UNARY */";
	}



	std::string transpile_expr(
		const sst::Reflect & expr,
		unsigned indentation,
		const lang::Language & lang) {

		return  "/* REFLECT */";
	}
}