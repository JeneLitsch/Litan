#include "optimize.hxx"
#include "ltn/casts.hxx"
#include "eval/eval_conditional.hxx"
namespace ltn::c {
	namespace {
		sst::stmt_ptr optimize_unary_statement(auto & stmt) {
			if(stmt.expression) {
				stmt.expression = optimize_expression(std::move(stmt.expression));
			}
			return nullptr;
		} 


		sst::stmt_ptr optimize_block(sst::Block & block) {
			for(auto & stmt : block.statements) {
				stmt = optimize_statement(std::move(stmt));
			}
			return nullptr;
		}



		sst::stmt_ptr optimize_if_else(sst::IfElse & stmt) {
			stmt.condition = optimize_expression(std::move(stmt.condition));
			stmt.if_branch = optimize_statement(std::move(stmt.if_branch));
			if(stmt.else_branch) {
				stmt.else_branch = optimize_statement(std::move(stmt.else_branch));
			}

			if(auto expr = pre_decide<sst::Null>(stmt))    return expr;
			if(auto expr = pre_decide<sst::Bool>(stmt))    return expr;
			if(auto expr = pre_decide<sst::Char>(stmt))    return expr;
			if(auto expr = pre_decide<sst::Integer>(stmt)) return expr;
			if(auto expr = pre_decide<sst::Float>(stmt))   return expr;
			if(auto expr = pre_decide<sst::String>(stmt))  return expr;
			if(auto expr = pre_decide<sst::Array>(stmt))   return expr;
			return nullptr;
		}



		sst::stmt_ptr to_infinite(sst::While & stmt) {
			return stx::make_unique<sst::InfiniteLoop>(
				std::move(stmt.body), stmt.location);
		}



		sst::stmt_ptr optimize_while_loop(sst::While & stmt) {
			stmt.condition = optimize_expression(std::move(stmt.condition));
			stmt.body = optimize_statement(std::move(stmt.body));

			if(is_truthy<sst::Null>(*stmt.condition))    return to_infinite(stmt);
			if(is_truthy<sst::Bool>(*stmt.condition))    return to_infinite(stmt);
			if(is_truthy<sst::Char>(*stmt.condition))    return to_infinite(stmt);
			if(is_truthy<sst::Integer>(*stmt.condition)) return to_infinite(stmt);
			if(is_truthy<sst::Float>(*stmt.condition))   return to_infinite(stmt);
			if(is_truthy<sst::String>(*stmt.condition))  return to_infinite(stmt);
			if(is_truthy<sst::Array>(*stmt.condition))   return to_infinite(stmt);

			return nullptr;
		}

		
		
		sst::stmt_ptr optimize_for_loop(sst::For & stmt) {
			stmt.from = optimize_expression(std::move(stmt.from));
			stmt.to = optimize_expression(std::move(stmt.to));
			stmt.body = optimize_statement(std::move(stmt.body));
			return nullptr;
		}
	}



	sst::stmt_ptr optimize_statement(sst::Statement & stmt) {
		if(auto s = as<sst::StatementExpression>(stmt)) {
			return optimize_unary_statement(*s);
		}
		if(auto s = as<sst::Return>(stmt)) {
			return optimize_unary_statement(*s);
		}
		if(auto s = as<sst::NewVar>(stmt)) {
			return optimize_unary_statement(*s);
		}
		if(auto s = as<sst::Throw>(stmt)) {
			return optimize_unary_statement(*s);
		}
		if(auto s = as<sst::Block>(stmt)) {
			return optimize_block(*s);
		}
		if(auto s = as<sst::IfElse>(stmt)) {
			return optimize_if_else(*s);
		}
		if(auto s = as<sst::While>(stmt)) {
			return optimize_while_loop(*s);
		}
		if(auto s = as<sst::For>(stmt)) {
			return optimize_for_loop(*s);
		}
		return nullptr;
	}



	sst::stmt_ptr optimize_statement(sst::stmt_ptr stmt) {
		if(auto s = optimize_statement(*stmt)) {
			return s;
		}
		return stmt;
	}
}