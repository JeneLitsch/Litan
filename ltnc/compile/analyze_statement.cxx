#include "compile.hxx"

namespace ltn::c  {
	sst::stmt_ptr analyze_stmt(const ast::Block & stmt, CompilerInfo & info, Scope & scope) {
		std::vector<sst::stmt_ptr> statements;
		for(const auto & s : stmt.statements) {
			statements.push_back(analyze_statement(*s, info, scope));
		}
		return stx::make_unique<sst::Block>(std::move(statements), stmt.location);
	}



	sst::stmt_ptr analyze_stmt(const ast::Return & stmt, CompilerInfo & info, Scope & scope) {
		if(stmt.expression) {
			auto expr = analyze_expression(*stmt.expression, info, scope);
			return std::make_unique<sst::Return>(std::move(expr), stmt.location);
		}
		return std::make_unique<sst::Return>(nullptr, stmt.location);
	}



	sst::stmt_ptr analyze_stmt(const ast::Assign & stmt, CompilerInfo & info, Scope & scope) {
		auto l = analyze_expression(*stmt.l, info, scope);
		auto r = analyze_expression(*stmt.r, info, scope);
		return std::make_unique<sst::Assign>(
			std::move(l),
			std::move(r),
			stmt.location
		);
	}



	sst::stmt_ptr analyze_stmt(const ast::Throw & stmt, CompilerInfo & info, Scope & scope) {
		if(stmt.expression) {
			auto expr = analyze_expression(*stmt.expression, info, scope);
			return std::make_unique<sst::Throw>(std::move(expr), stmt.location);
		}
		return std::make_unique<sst::Throw>(nullptr, stmt.location);
	}



	sst::stmt_ptr analyze_stmt(const ast::InitMember & stmt, CompilerInfo & info, Scope & scope) {
		return stx::make_unique<sst::InitMember>(
			stmt.member, stmt.param, stmt.type, stmt.location
		);
	}



	sst::stmt_ptr analyze_stmt(const ast::IfElse & stmt, CompilerInfo & info, Scope & scope) {
		auto condition = analyze_expression(*stmt.condition, info, scope);
		auto if_branch = analyze_statement(*stmt.if_branch, info, scope);
		if(stmt.else_branch) {
			auto else_branch = analyze_statement(*stmt.else_branch, info, scope);
			return stx::make_unique<sst::IfElse>(
				std::move(condition),
				std::move(if_branch),
				std::move(else_branch),
				stmt.location
			);
		}
		else {
			return stx::make_unique<sst::IfElse>(
				std::move(condition),
				std::move(if_branch),
				nullptr,
				stmt.location
			);
		}
	}



	sst::stmt_ptr analyze_stmt(const ast::InfiniteLoop & stmt, CompilerInfo & info, Scope & scope) {
		auto body = analyze_statement(*stmt.body, info, scope);
		return stx::make_unique<sst::InfiniteLoop>(std::move(body), stmt.location);
	}



	sst::stmt_ptr analyze_stmt(const ast::While & stmt, CompilerInfo & info, Scope & scope) {
		auto condition = analyze_expression(*stmt.condition, info, scope);
		auto body = analyze_statement(*stmt.body, info, scope);
		return stx::make_unique<sst::While>(
			std::move(condition),
			std::move(body),
			stmt.location
		);
	}



	sst::stmt_ptr analyze_stmt(const ast::For & stmt, CompilerInfo & info, Scope & scope) {
		auto var = analyze_stmt(*stmt.var, info, scope);
		auto from = analyze_expression(*stmt.from, info, scope);
		auto to = analyze_expression(*stmt.to, info, scope);
		auto step = stmt.step ? analyze_expression(*stmt.step, info, scope) : nullptr;
		auto body = analyze_statement(*stmt.body, info, scope);
		return stx::make_unique<sst::For>(
			std::move(var),
			std::move(from),
			std::move(to),
			std::move(step),
			std::move(body),
			stmt.location
		);
	}



	std::unique_ptr<sst::NewVar> analyze_stmt(const ast::NewVar & stmt, CompilerInfo & info, Scope & scope) {
		if(stmt.expression) {
			auto expr = analyze_expression(*stmt.expression, info, scope);
			return std::make_unique<sst::NewVar>(stmt.name, std::move(expr), stmt.location, stmt.type);
		}
		return std::make_unique<sst::NewVar>(stmt.name, nullptr, stmt.location, stmt.type);
	}



	sst::stmt_ptr analyze_stmt(const ast::StmtSwitch & stmt, CompilerInfo & info, Scope & scope) {
		auto stmt_switch = std::make_unique<sst::StmtSwitch>(stmt.location);
		stmt_switch->condition  = analyze_expression(*stmt.condition, info, scope);
		for(const auto & [expr, c4se] : stmt.cases) {
			auto sst_expr = analyze_expression(*expr, info, scope);
			auto sst_case = analyze_statement(*c4se, info, scope);
			stmt_switch->cases.push_back({
				std::move(sst_expr),
				std::move(sst_case)
			});
		}
		if(stmt.d3fault) {
			stmt_switch->d3fault = analyze_statement(*stmt.d3fault, info, scope);
		}
		return stmt_switch;
	}



	sst::stmt_ptr analyze_stmt(const ast::DoNothing & stmt, CompilerInfo & info, Scope & scope) {
		return stx::make_unique<sst::DoNothing>(stmt.location);
	}


	sst::stmt_ptr analyze_stmt(const ast::StatementExpression & stmt, CompilerInfo & info, Scope & scope) {
		auto expr = analyze_expression(*stmt.expression, info, scope);
		return stx::make_unique<sst::StatementExpression>(
			std::move(expr),
			stmt.location
		);
	}

	
	sst::stmt_ptr analyze_statement(const ast::Statement & stmt, CompilerInfo & info, Scope & scope) {
		return ast::visit_statement(stmt, [&] (const auto & s) -> sst::stmt_ptr {
			return analyze_stmt(s, info, scope);
		});
	}
}