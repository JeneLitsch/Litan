#include "optimize.hxx"
#include "ltn/casts.hxx"
#include "eval/eval_conditional.hxx"
namespace ltn::c {
	namespace {
		ast::stmt_ptr optimize_unary_statement(auto & stmt) {
			if(stmt.expression) {
				stmt.expression = optimize_expression(std::move(stmt.expression));
			}
			return nullptr;
		} 


		ast::stmt_ptr optimize_block(ast::Block & block) {
			for(auto & stmt : block.statements) {
				stmt = optimize_statement(std::move(stmt));
			}
			return nullptr;
		}



		ast::stmt_ptr optimize_if_else(ast::IfElse & stmt) {
			stmt.condition = optimize_expression(std::move(stmt.condition));
			stmt.if_branch = optimize_statement(std::move(stmt.if_branch));
			if(stmt.else_branch) {
				stmt.else_branch = optimize_statement(std::move(stmt.else_branch));
			}

			if(auto expr = pre_decide<ast::Null>(stmt))    return expr;
			if(auto expr = pre_decide<ast::Bool>(stmt))    return expr;
			if(auto expr = pre_decide<ast::Char>(stmt))    return expr;
			if(auto expr = pre_decide<ast::Integer>(stmt)) return expr;
			if(auto expr = pre_decide<ast::Float>(stmt))   return expr;
			if(auto expr = pre_decide<ast::String>(stmt))  return expr;
			if(auto expr = pre_decide<ast::Array>(stmt))   return expr;
			return nullptr;
		}



		ast::stmt_ptr to_infinite(ast::While & stmt) {
			return stx::make_unique<ast::InfiniteLoop>(
				std::move(stmt.body), stmt.location);
		}



		ast::stmt_ptr optimize_while_loop(ast::While & stmt) {
			stmt.condition = optimize_expression(std::move(stmt.condition));
			stmt.body = optimize_statement(std::move(stmt.body));

			if(is_truthy<ast::Null>(*stmt.condition))    return to_infinite(stmt);
			if(is_truthy<ast::Bool>(*stmt.condition))    return to_infinite(stmt);
			if(is_truthy<ast::Char>(*stmt.condition))    return to_infinite(stmt);
			if(is_truthy<ast::Integer>(*stmt.condition)) return to_infinite(stmt);
			if(is_truthy<ast::Float>(*stmt.condition))   return to_infinite(stmt);
			if(is_truthy<ast::String>(*stmt.condition))  return to_infinite(stmt);
			if(is_truthy<ast::Array>(*stmt.condition))   return to_infinite(stmt);

			return nullptr;
		}

		
		
		ast::stmt_ptr optimize_for_loop(ast::For & stmt) {
			stmt.from = optimize_expression(std::move(stmt.from));
			stmt.to = optimize_expression(std::move(stmt.to));
			stmt.body = optimize_statement(std::move(stmt.body));
			return nullptr;
		}
	}



	ast::stmt_ptr optimize_statement(ast::Statement & stmt) {
		if(auto s = as<ast::StatementExpression>(stmt)) {
			return optimize_unary_statement(*s);
		}
		if(auto s = as<ast::Return>(stmt)) {
			return optimize_unary_statement(*s);
		}
		if(auto s = as<ast::NewVar>(stmt)) {
			return optimize_unary_statement(*s);
		}
		if(auto s = as<ast::Throw>(stmt)) {
			return optimize_unary_statement(*s);
		}
		if(auto s = as<ast::Block>(stmt)) {
			return optimize_block(*s);
		}
		if(auto s = as<ast::IfElse>(stmt)) {
			return optimize_if_else(*s);
		}
		if(auto s = as<ast::While>(stmt)) {
			return optimize_while_loop(*s);
		}
		if(auto s = as<ast::For>(stmt)) {
			return optimize_for_loop(*s);
		}
		return nullptr;
	}



	ast::stmt_ptr optimize_statement(ast::stmt_ptr stmt) {
		if(auto s = optimize_statement(*stmt)) {
			return s;
		}
		return stmt;
	}
}