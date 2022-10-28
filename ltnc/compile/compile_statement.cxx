#include "compile.hxx"
namespace ltn::c {
	StmtResult compile_expr_stmt(const ast::StatementExpression & stmt, CompilerInfo & info, Scope & scope) {
		const auto code = compile_expression(*stmt.expression, info, scope);
		InstructionBuffer buf;
		buf << code.code;
		buf << inst::scrap();
		return { buf, 0 };
	}



	StmtResult compile_statement(const ast::Statement & stmt, CompilerInfo & info, Scope & scope) {
		if(auto block = as<ast::Block>(stmt)) {
			return compile_block(*block, info, scope);
		}
		if(auto if_else = as<ast::IfElse>(stmt)) {
			return compile_if_else(*if_else, info, scope);
		}
		if(auto loop = as<ast::While>(stmt)) {
			return compile_while_loop(*loop, info, scope);
		}
		if(auto loop = as<ast::InfiniteLoop>(stmt)) {
			return compile_infinite_loop(*loop, info, scope);
		}
		if(auto loop = as<ast::For>(stmt)) {
			return compile_for_loop(*loop, info, scope);
		}
		if(auto new_variable = as<ast::NewVar>(stmt)) {
			return compile_new_variable(*new_variable, info, scope);
		}
		if(auto reTurn = as<ast::Return>(stmt)) {
			return compile_reTurn(*reTurn, info, scope);
		}
		if(auto thr0w = as<ast::Throw>(stmt)) {
			return compile_thr0w(*thr0w, info, scope);
		}
		if(auto init = as<ast::InitMember>(stmt)) {
			return compile_init_member(*init, info, scope);
		}
		if(auto sw1tch = as<ast::StmtSwitch>(stmt)) {
			return compile_stmt_switch(*sw1tch, info, scope);
		}
		if(auto exprstmt = as<ast::StatementExpression>(stmt)) {
			return compile_expr_stmt(*exprstmt, info, scope);
		}
		if(as<ast::DoNothing>(stmt)) {
			return StmtResult{{}, 0};
		}
		if(auto assign = as<ast::Assign>(stmt)) {
			return compile_assign(*assign, info, scope);
		}
		throw CompilerError{"Unknown statement"};
	}
}