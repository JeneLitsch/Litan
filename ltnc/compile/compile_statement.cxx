#include "compile.hxx"
namespace ltn::c::compile {
	StmtCode expr_stmt(const ast::StatementExpression & stmt, CompilerInfo & info, Scope & scope) {
		const auto code = expression(*stmt.expression, info, scope);
		std::stringstream ss;
		ss << code.code;
		ss << inst::scrap;
		return { ss.str(), 0 };
	}


	// compiles statement
	StmtCode statement(const ast::Statement & stmt, CompilerInfo & info, Scope & scope) {
		if(auto block = as<ast::Block>(stmt)) {
			return compile::block(*block, info, scope);
		}
		if(auto if_else = as<ast::IfElse>(stmt)) {
			return compile::if_else(*if_else, info, scope);
		}
		if(auto loop = as<ast::While>(stmt)) {
			return compile::while_loop(*loop, info, scope);
		}
		if(auto loop = as<ast::InfiniteLoop>(stmt)) {
			return compile::infinite_loop(*loop, info, scope);
		}
		if(auto loop = as<ast::For>(stmt)) {
			return compile::for_loop(*loop, info, scope);
		}
		if(auto new_variable = as<ast::NewVar>(stmt)) {
			return compile::new_variable(*new_variable, info, scope);
		}
		if(auto reTurn = as<ast::Return>(stmt)) {
			return compile::reTurn(*reTurn, info, scope);
		}
		if(auto thr0w = as<ast::Throw>(stmt)) {
			return compile::thr0w(*thr0w, info, scope);
		}
		if(auto init = as<ast::InitMember>(stmt)) {
			return compile::init_member(*init, info, scope);
		}
		if(auto exprstmt = as<ast::StatementExpression>(stmt)) {
			return compile::expr_stmt(*exprstmt, info, scope);
		}
		if(as<ast::DoNothing>(stmt)) {
			return StmtCode{"", 0};
		}
		if(auto assign = as<ast::Assign>(stmt)) {
			return compile::assign(*assign, info, scope);
		}
		if(auto modify = as<ast::Modify>(stmt)) {
			return compile::modify(*modify, info, scope);
		}
		throw CompilerError{"Unknown statement"};
	}
}