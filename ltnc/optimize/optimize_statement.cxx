#include "optimize.hxx"
#include "ltn/casts.hxx"
#include "eval/eval_conditional.hxx"
#include "ltnc/sst/expr/Array.hxx"
#include "ltnc/sst/expr/Literal.hxx"
#include "ltnc/sst/stmt/Assign.hxx"
#include "ltnc/sst/stmt/Block.hxx"
#include "ltnc/sst/stmt/IfElse.hxx"
#include "ltnc/sst/stmt/Return.hxx"
#include "ltnc/sst/stmt/Throw.hxx"
#include "ltnc/sst/stmt/ForEach.hxx"
#include "ltnc/sst/stmt/InfiniteLoop.hxx"
#include "ltnc/sst/stmt/While.hxx"

namespace ltn::c {
	namespace {
		sst::stmt_ptr optimize_unary_statement(auto & stmt) {
			if(stmt.expr) {
				stmt.expr = optimize_expression(std::move(stmt.expr));
			}
			return nullptr;
		} 



		sst::stmt_ptr optimize_block(sst::stmt::Block & block) {
			for(auto & stmt : block.statements) {
				stmt = optimize_statement(std::move(stmt));
			}
			return nullptr;
		}



		sst::stmt_ptr optimize_if_else(sst::stmt::IfElse & stmt) {
			stmt.condition = optimize_expression(std::move(stmt.condition));
			stmt.if_branch = optimize_statement(std::move(stmt.if_branch));
			if(stmt.else_branch) {
				stmt.else_branch = optimize_statement(std::move(stmt.else_branch));
			}

			if(auto expr = pre_decide<sst::expr::Null>(stmt))    return expr;
			if(auto expr = pre_decide<sst::expr::Bool>(stmt))    return expr;
			if(auto expr = pre_decide<sst::expr::Integer>(stmt)) return expr;
			if(auto expr = pre_decide<sst::expr::Float>(stmt))   return expr;
			if(auto expr = pre_decide<sst::expr::String>(stmt))  return expr;
			if(auto expr = pre_decide<sst::expr::Array>(stmt))   return expr;
			return nullptr;
		}



		sst::stmt_ptr to_infinite(sst::stmt::While & stmt) {
			return sst::stmt::infinite_loop(std::move(stmt.body));
		}



		sst::stmt_ptr optimize_while_loop(sst::stmt::While & stmt) {
			stmt.condition = optimize_expression(std::move(stmt.condition));
			stmt.body = optimize_statement(std::move(stmt.body));

			if(is_truthy<sst::expr::Null>(*stmt.condition))    return to_infinite(stmt);
			if(is_truthy<sst::expr::Bool>(*stmt.condition))    return to_infinite(stmt);
			if(is_truthy<sst::expr::Integer>(*stmt.condition)) return to_infinite(stmt);
			if(is_truthy<sst::expr::Float>(*stmt.condition))   return to_infinite(stmt);
			if(is_truthy<sst::expr::String>(*stmt.condition))  return to_infinite(stmt);
			if(is_truthy<sst::expr::Array>(*stmt.condition))   return to_infinite(stmt);

			return nullptr;
		}
	}



	sst::stmt_ptr optimize_statement(sst::stmt::Statement & stmt) {
		if(auto s = as<sst::stmt::Return>(stmt)) {
			return optimize_unary_statement(*s);
		}
		if(auto s = as<sst::stmt::Assign>(stmt)) {
			return optimize_unary_statement(*s);
		}
		if(auto s = as<sst::stmt::Throw>(stmt)) {
			return optimize_unary_statement(*s);
		}
		if(auto s = as<sst::stmt::Block>(stmt)) {
			return optimize_block(*s);
		}
		if(auto s = as<sst::stmt::IfElse>(stmt)) {
			return optimize_if_else(*s);
		}
		if(auto s = as<sst::stmt::While>(stmt)) {
			return optimize_while_loop(*s);
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