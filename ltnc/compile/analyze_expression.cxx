#include "compile.hxx"

namespace ltn::c {
	auto analyze_captures(const std::vector<std::unique_ptr<ast::Var>> & captures) {
		std::vector<std::unique_ptr<sst::Var>> sst_captures;
		for(const auto & c : captures) {
			sst_captures.push_back(stx::make_unique<sst::Var>(
				c->name,
				c->namespaze,
				c->location
			));
		}
		return sst_captures;
	}


	sst::expr_ptr analyze_expr(const ast::Lambda & expr, CompilerInfo & info, Scope & scope) {
		auto fx = analyze_function(*expr.fx, info, scope);
		auto captures = analyze_captures(expr.captures);
		return stx::make_unique<sst::Lambda>(
			std::move(fx),
			std::move(captures),
			expr.location
		);
	}



	sst::expr_ptr analyze_expr(const ast::ExprSwitch & expr, CompilerInfo & info, Scope & scope) {
		auto expr_switch = std::make_unique<sst::ExprSwitch>(expr.location);
		expr_switch->condition  = analyze_expression(*expr.condition, info, scope);
		for(const auto & [expr, c4se] : expr.cases) {
			auto sst_expr = analyze_expression(*expr, info, scope);
			auto sst_case = analyze_expression(*c4se, info, scope);
			expr_switch->cases.push_back({
				std::move(sst_expr),
				std::move(sst_case)
			});
		}
		if(expr.d3fault) {
			expr_switch->d3fault = analyze_expression(*expr.d3fault, info, scope);
		}
		return expr_switch;
	}



	sst::expr_ptr analyze_expr(const ast::Ternary & expr, CompilerInfo & info, Scope & scope) {
		return stx::make_unique<sst::Ternary>(
			expr.location,
			analyze_expression(*expr.condition, info, scope),
			analyze_expression(*expr.if_branch, info, scope),
			analyze_expression(*expr.else_branch, info, scope)
		);
	}



	sst::expr_ptr analyze_expr(const ast::Binary & expr, CompilerInfo & info, Scope & scope) {
		auto l = analyze_expression(*expr.l, info, scope);
		auto r = analyze_expression(*expr.r, info, scope);
		
		return stx::make_unique<sst::Binary>(
			static_cast<sst::Binary::Type>(expr.type),
			std::move(l),
			std::move(r),
			expr.location
		);
	}



	sst::expr_ptr analyze_expr(const ast::Unary & expr, CompilerInfo & info, Scope & scope) {
		return stx::make_unique<sst::Unary>(
			static_cast<sst::Unary::Type>(expr.type),
			analyze_expression(*expr.expression, info, scope),
			expr.location
		);
	}



	sst::expr_ptr analyze_expr(const ast::Integer & expr, CompilerInfo & info, Scope & scope) {
		return stx::make_unique<sst::Integer>(
			expr.value,
			expr.location
		);
	}



	sst::expr_ptr analyze_expr(const ast::Float & expr, CompilerInfo & info, Scope & scope) {
		return stx::make_unique<sst::Float>(
			expr.value,
			expr.location
		);
	}



	sst::expr_ptr analyze_expr(const ast::Bool & expr, CompilerInfo & info, Scope & scope) {
		return stx::make_unique<sst::Bool>(
			expr.value,
			expr.location
		);
	}



	sst::expr_ptr analyze_expr(const ast::Char & expr, CompilerInfo & info, Scope & scope) {
		return stx::make_unique<sst::Char>(
			expr.value,
			expr.location
		);
	}



	sst::expr_ptr analyze_expr(const ast::Null & expr, CompilerInfo & info, Scope & scope) {
		return stx::make_unique<sst::Null>(expr.location);
	}



	sst::expr_ptr analyze_expr(const ast::String & expr, CompilerInfo & info, Scope & scope) {
		return stx::make_unique<sst::String>(
			expr.value,
			expr.location
		);
	}



	sst::expr_ptr analyze_expr(const ast::Array & expr, CompilerInfo & info, Scope & scope) {
		std::vector<sst::expr_ptr> elements;
		for(const auto & elem : expr.elements) {
			elements.push_back(analyze_expression(*elem, info, scope));
		}
		auto arr = stx::make_unique<sst::Array>(expr.location);
		arr->elements = std::move(elements);
		return arr;
	}



	sst::expr_ptr analyze_expr(const ast::Call & expr, CompilerInfo & info, Scope & scope) {
		auto function_ptr = analyze_expression(*expr.function_ptr, info, scope); 
		std::vector<sst::expr_ptr> parameters;
		for(const auto & param : expr.parameters) {
			parameters.push_back(analyze_expression(*param, info, scope));
		}
		auto call = stx::make_unique<sst::Call>(
			std::move(function_ptr),
			std::move(parameters),
			expr.location
		);
		call->template_args = expr.template_args;
		return call;
	}



	sst::expr_ptr analyze_expr(const ast::Index & expr, CompilerInfo & info, Scope & scope) {
		auto expression = analyze_expression(*expr.expression, info, scope);
		auto index = analyze_expression(*expr.index, info, scope);
		return stx::make_unique<sst::Index>(
			std::move(expression),
			std::move(index),
			expr.location
		);
	}



	sst::expr_ptr analyze_expr(const ast::FxPointer & expr, CompilerInfo & info, Scope & scope) {
		auto fx_ptr = stx::make_unique<sst::FxPointer>(
			expr.name,
			expr.namespaze,
			expr.placeholders,
			expr.location
		);
		fx_ptr->template_arguements = expr.template_arguements;
		return fx_ptr;
	}



	sst::expr_ptr analyze_expr(const ast::Iife & expr, CompilerInfo & info, Scope & scope) {
		auto statement = analyze_statement(*expr.stmt, info, scope);
		return stx::make_unique<sst::Iife>(
			expr.location,
			std::move(statement),
			expr.return_type
		);
	}



	sst::expr_ptr analyze_expr(const ast::Var & expr, CompilerInfo & info, Scope & scope) {
		return stx::make_unique<sst::Var>(
			expr.name,
			expr.namespaze,
			expr.location
		);
	}



	sst::expr_ptr analyze_expr(const ast::Member & expr, CompilerInfo & info, Scope & scope) {
		auto expression = analyze_expression(*expr.expr, info, scope);
		return stx::make_unique<sst::Member>(
			std::move(expression),
			expr.name,
			expr.location
		);
	}



	sst::expr_ptr analyze_expr(const ast::GlobalVar & expr, CompilerInfo & info, Scope & scope) {
		return stx::make_unique<sst::GlobalVar>(
			expr.location,
			expr.namespaze,
			expr.name
		);
	}



	sst::expr_ptr analyze_expr(const ast::TypedUnary & expr, CompilerInfo & info, Scope & scope) {
		auto expression = analyze_expression(*expr.expr, info, scope);
		return stx::make_unique<sst::TypedUnary>(
			static_cast<sst::TypedUnary::Op>(expr.op),
			expr.type,
			std::move(expression),
			expr.location
		);
	}



	sst::expr_ptr analyze_expr(const ast::Reflect & expr, CompilerInfo & info, Scope & scope) {
		return stx::make_unique<sst::Reflect>(expr.query, expr.location);
	}


	sst::expr_ptr analyze_expr(const ast::DeclType & expr, CompilerInfo & info, Scope & scope) {
		auto expression = analyze_expression(*expr.expression, info, scope);
		return stx::make_unique<sst::DeclType>(
			std::move(expression),
			expr.location
		);
	}



	sst::expr_ptr analyze_expression(const ast::Expression & expr, CompilerInfo & info, Scope & scope) {
		return ast::visit_expression(expr, [&](const auto & e) {
			return analyze_expr(e, info, scope);
		});
	}
}