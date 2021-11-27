#include "compiling.hxx"

namespace ltn::c::compile {
	namespace {
		// compiles -> code block {...}
		StmtCode block(const ast::Block & block, CompilerInfo & info, Scope & parent) {
			Scope scope(&parent);
			std::stringstream ss;
			std::size_t varCount = 0;
			for(const auto & stmt : block.statements) {
				if(stmt) {
					const auto compiled = statement(*stmt, info, scope); 
					ss << compiled.code;
					varCount += compiled.varCount;
				} 
			}
			return {ss.str(), varCount};
		}

		// compiles -> return...;
		StmtCode reTurn(const ast::Return & ret, CompilerInfo & info, Scope & scope) {
			std::stringstream ss;
			if(ret.expression) {
				auto code = compile::expression(*ret.expression, info, scope);
				ss << code.code;
			}
			else {
				ss << inst::null;
			}
			ss << inst::reTurn;
			return {ss.str(), 0};
		}
		
	}
	// compiles variable creation -> var foo ...;
	StmtCode newVar(const ast::NewVar & newVar, CompilerInfo & info, Scope & scope) {
		const auto addr = scope.insert(newVar.name, newVar.debugInfo.line);
		std::stringstream ss;
		if(newVar.right) {
			const auto expr = compile::expression(*newVar.right, info, scope);
			ss << expr.code;
		}
		else {
			ss << inst::null;
		}
		ss << inst::write_x(addr);
		return {ss.str(), 1};
	}


	// compiles statement
	StmtCode statement(const ast::Statement & stmt, CompilerInfo & info, Scope & scope) {
		if(auto block = as<ast::Block>(stmt)) {
			return compile::block(*block, info, scope);
		}
		if(auto ifElse = as<ast::IfElse>(stmt)) {
			return compile::ifElse(*ifElse, info, scope);
		}
		if(auto loop = as<ast::While>(stmt)) {
			return compile::whileLoop(*loop, info, scope);
		}
		if(auto loop = as<ast::For>(stmt)) {
			return compile::forLoop(*loop, info, scope);
		}
		if(auto newVar = as<ast::NewVar>(stmt)) {
			return compile::newVar(*newVar, info, scope);
		}
		if(auto reTurn = as<ast::Return>(stmt)) {
			return compile::reTurn(*reTurn, info, scope);
		}
		if(auto exprstmt = as<ast::StatementExpression>(stmt)) {
			const auto code = expression(*exprstmt->expression, info, scope);
			std::stringstream ss;
			ss << code.code;
			ss << inst::scrap;
			return { ss.str(), 0 };
		}
		return { "...STMT\n" , 0 };
	}
}