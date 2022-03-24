#include "optimize.hxx"
#include "ltn/casts.hxx"
namespace ltn::c::optimize {
	namespace {
		ast::stmt_ptr unary_statement(auto & stmt) {
			stmt.expression = expression(std::move(stmt.expression));
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
			return nullptr;
		}



		ast::stmt_ptr while_loop(ast::While & stmt) {
			stmt.condition = expression(std::move(stmt.condition));
			stmt.body = statement(std::move(stmt.body));
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
		if(auto s = as<ast::NewConst>(stmt)) {
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