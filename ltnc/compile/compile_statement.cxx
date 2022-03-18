#include "compile.hxx"
namespace ltn::c::compile {
	namespace {
		// compiles -> code block {...}
		StmtCode block(const ast::Block & block, CompilerInfo & info, Scope & parent) {
			Scope scope(&parent);
			std::stringstream ss;
			std::size_t locals = 0;
			std::size_t newAllocs = 0;
			for(const auto & stmt : block.statements) {
				try {
					if(stmt) {
						const auto compiled = compile::statement(*stmt, info, scope); 
						ss << compiled.code;
						locals = std::max(locals, compiled.var_count);
						newAllocs += compiled.direct_allocation;
					} 
				}
				catch(const CompilerError & error) {
					info.reporter.push(error);
				}
			}
			return {ss.str(), locals + newAllocs, false};
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

			// For returns from iife
			if(const auto returns_to = scope.get_return()) {
				ss << inst::jump(*returns_to);
			}
			else {
				ss << inst::reTurn;
			}
			return {ss.str(), 0};
		}

		// compiles variable creation -> var foo ...;
		StmtCode new_variable_like(
			const auto & new_variable,
			CompilerInfo & info,
			Scope & scope,
			Variable::Qualifier qualifier) {
			
			const auto var = scope.insert(
				new_variable.name, qualifier, new_variable.location);
			std::stringstream ss;
			if(new_variable.right) {
				const auto expr = compile::expression(*new_variable.right, info, scope);
				ss << expr.code;
			}
			else {
				ss << inst::null;
			}
			ss << inst::write_x(var.address);
			return {ss.str(), 0, true};
		}		
	}
	

	StmtCode new_const(const ast::NewConst & stmt, CompilerInfo & info, Scope & scope) {
		return new_variable_like(stmt, info, scope, Variable::Qualifier::CONST);
	}
	

	StmtCode new_variable(const ast::NewVar & stmt, CompilerInfo & info, Scope & scope) {
		return new_variable_like(stmt, info, scope, Variable::Qualifier::MUTABLE);
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
		if(auto if_else = as<ast::IfElse>(stmt)) {
			return compile::if_else(*if_else, info, scope);
		}
		if(auto loop = as<ast::While>(stmt)) {
			return compile::while_loop(*loop, info, scope);
		}
		if(auto loop = as<ast::For>(stmt)) {
			return compile::for_loop(*loop, info, scope);
		}
		if(auto new_variable = as<ast::NewVar>(stmt)) {
			return compile::new_variable(*new_variable, info, scope);
		}
		if(auto new_const = as<ast::NewConst>(stmt)) {
			return compile::new_const(*new_const, info, scope);
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
		throw CompilerError{"Unknown statement"};
	}
}