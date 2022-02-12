#include "compiling.hxx"
namespace ltn::c::compile {
	namespace {
		// compiles -> code block {...}
		StmtCode block(const ast::Block & block, CompilerInfo & info, Scope & parent) {
			Scope scope(&parent);
			std::stringstream ss;
			std::size_t varCount = 0;
			std::size_t newAllocs = 0;
			for(const auto & stmt : block.statements) {
				try {
					if(stmt) {
						const auto compiled = compile::statement(*stmt, info, scope); 
						ss << compiled.code;
						varCount = std::max(varCount, compiled.varCount);
						newAllocs += compiled.directAllocation;
					} 
				}
				catch(const CompilerError & error) {
					info.reporter.push(error);
				}
			}
			return {ss.str(), varCount + newAllocs, false};
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

		// compiles variable creation -> var foo ...;
		StmtCode newVariablelike(
			const auto & newVar,
			CompilerInfo & info,
			Scope & scope,
			Variable::Qualifier qualifier) {
			
			const auto var = scope.insert(
				newVar.name, qualifier, newVar.location);
			std::stringstream ss;
			if(newVar.right) {
				const auto expr = compile::expression(*newVar.right, info, scope);
				ss << expr.code;
			}
			else {
				ss << inst::null;
			}
			ss << inst::write_x(var.address);
			return {ss.str(), 0, true};
		}		
	}
	

	StmtCode newConst(const ast::NewConst & stmt, CompilerInfo & info, Scope & scope) {
		return newVariablelike(stmt, info, scope, Variable::Qualifier::CONST);
	}
	

	StmtCode newVar(const ast::NewVar & stmt, CompilerInfo & info, Scope & scope) {
		return newVariablelike(stmt, info, scope, Variable::Qualifier::MUTABLE);
	}


	StmtCode thr0w(const ast::Throw & thr0w, CompilerInfo & info, Scope & scope) {
		std::ostringstream ss;
		if(thr0w.expr) {
			ss << compile::expression(*thr0w.expr, info, scope).code;
		}
		else {
			ss << inst::null;
		}
		ss << inst::thr0w;
		return {ss.str(), 0};
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
		if(auto newConst = as<ast::NewConst>(stmt)) {
			return compile::newConst(*newConst, info, scope);
		}
		if(auto reTurn = as<ast::Return>(stmt)) {
			return compile::reTurn(*reTurn, info, scope);
		}
		if(auto thr0w = as<ast::Throw>(stmt)) {
			return compile::thr0w(*thr0w, info, scope);
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