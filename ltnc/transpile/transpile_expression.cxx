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

	}



	std::string transpile_expr(
		const sst::ExprSwitch & expr,
		unsigned indentation,
		const lang::Language & lang) {

	}



	std::string transpile_expr(
		const sst::Ternary & expr,
		unsigned indentation,
		const lang::Language & lang) {

	}



	std::string transpile_expr(
		const sst::Binary & expr,
		unsigned indentation,
		const lang::Language & lang) {

	}



	std::string transpile_expr(
		const sst::Unary & expr,
		unsigned indentation,
		const lang::Language & lang) {

	}



	std::string transpile_expr(
		const sst::Integer & expr,
		unsigned indentation,
		const lang::Language & lang) {

	}



	std::string transpile_expr(
		const sst::Float & expr,
		unsigned indentation,
		const lang::Language & lang) {

	}



	std::string transpile_expr(
		const sst::Bool & expr,
		unsigned indentation,
		const lang::Language & lang) {

	}



	std::string transpile_expr(
		const sst::Char & expr,
		unsigned indentation,
		const lang::Language & lang) {

	}



	std::string transpile_expr(
		const sst::Null & expr,
		unsigned indentation,
		const lang::Language & lang) {

	}



	std::string transpile_expr(
		const sst::String & expr,
		unsigned indentation,
		const lang::Language & lang) {

	}



	std::string transpile_expr(
		const sst::Array & expr,
		unsigned indentation,
		const lang::Language & lang) {

	}



	std::string transpile_expr(
		const sst::Tuple & expr,
		unsigned indentation,
		const lang::Language & lang) {

	}



	std::string transpile_expr(
		const sst::Call & expr,
		unsigned indentation,
		const lang::Language & lang) {

	}



	std::string transpile_expr(
		const sst::Invoke & expr,
		unsigned indentation,
		const lang::Language & lang) {

	}



	std::string transpile_expr(
		const sst::Index & expr,
		unsigned indentation,
		const lang::Language & lang) {

	}



	std::string transpile_expr(
		const sst::FxPointer & expr,
		unsigned indentation,
		const lang::Language & lang) {

	}



	std::string transpile_expr(
		const sst::Iife & expr,
		unsigned indentation,
		const lang::Language & lang) {

	}



	std::string transpile_expr(
		const sst::Var & expr,
		unsigned indentation,
		const lang::Language & lang) {

	}



	std::string transpile_expr(
		const sst::Member & expr,
		unsigned indentation,
		const lang::Language & lang) {

	}



	std::string transpile_expr(
		const sst::GlobalVar & expr,
		unsigned indentation,
		const lang::Language & lang) {

	}



	std::string transpile_expr(
		const sst::TypedUnary & expr,
		unsigned indentation,
		const lang::Language & lang) {

	}



	std::string transpile_expr(
		const sst::Reflect & expr,
		unsigned indentation,
		const lang::Language & lang) {

	}
}