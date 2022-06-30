#include "optimize.hxx"
#include "ltn/casts.hxx"
#include "eval/eval_conditional.hxx"
namespace ltn::c::optimize {
	namespace {
		ast::stmt_ptr unary_statement(auto & stmt) {
			if(stmt.expression) {
				stmt.expression = expression(std::move(stmt.expression));
			}
			return nullptr;
		} 


		ast::stmt_ptr block(ast::Block & block) {
			for(auto & stmt : block.statements) {
				stmt = statement(std::move(stmt));
			}
			return nullptr;
		}



		ast::stmt_ptr if_else(ast::IfElse & stmt) {
			stmt.condition = expression(std::move(stmt.condition));
			stmt.if_branch = statement(std::move(stmt.if_branch));
			if(stmt.else_branch) {
				stmt.else_branch = statement(std::move(stmt.else_branch));
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
			return std::make_unique<ast::InfiniteLoop>(
				std::move(stmt.body), stmt.location);
		}



		ast::stmt_ptr while_loop(ast::While & stmt) {
			stmt.condition = expression(std::move(stmt.condition));
			stmt.body = statement(std::move(stmt.body));

			if(is_truthy<ast::Null>(*stmt.condition))    return to_infinite(stmt);
			if(is_truthy<ast::Bool>(*stmt.condition))    return to_infinite(stmt);
			if(is_truthy<ast::Char>(*stmt.condition))    return to_infinite(stmt);
			if(is_truthy<ast::Integer>(*stmt.condition)) return to_infinite(stmt);
			if(is_truthy<ast::Float>(*stmt.condition))   return to_infinite(stmt);
			if(is_truthy<ast::String>(*stmt.condition))  return to_infinite(stmt);
			if(is_truthy<ast::Array>(*stmt.condition))   return to_infinite(stmt);

			return nullptr;
		}

		
		
		ast::stmt_ptr for_loop(ast::For & stmt) {
			stmt.from = expression(std::move(stmt.from));
			stmt.to = expression(std::move(stmt.to));
			stmt.body = statement(std::move(stmt.body));
			return nullptr;
		}
	}



	ast::stmt_ptr statement(ast::Statement & stmt) {
		if(auto s = as<ast::StatementExpression>(stmt)) {
			return unary_statement(*s);
		}
		if(auto s = as<ast::Return>(stmt)) {
			return unary_statement(*s);
		}
		if(auto s = as<ast::NewVar>(stmt)) {
			return unary_statement(*s);
		}
		if(auto s = as<ast::Throw>(stmt)) {
			return unary_statement(*s);
		}
		if(auto s = as<ast::Block>(stmt)) {
			return block(*s);
		}
		if(auto s = as<ast::IfElse>(stmt)) {
			return if_else(*s);
		}
		if(auto s = as<ast::While>(stmt)) {
			return while_loop(*s);
		}
		if(auto s = as<ast::For>(stmt)) {
			return for_loop(*s);
		}
		return nullptr;
	}



	ast::stmt_ptr statement(ast::stmt_ptr stmt) {
		if(auto s = statement(*stmt)) {
			return s;
		}
		return stmt;
	}
}