#pragma once
#include <sstream>
#include "utils.hxx"
#include "Scope.hxx"
#include "FxTable.hxx"
#include "Instructions.hxx"
#include "StmtCode.hxx"
#include "ExprCode.hxx"
#include "ltnc/Config.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/ast/Node.hxx"
#include "ltnc/ast/Source.hxx"
#include "ltnc/ast/Function.hxx"
#include "ltnc/ast/Expression.hxx"
#include "ltnc/ast/Statement.hxx"
#include "ltnc/ast/Literals.hxx"
#include "ltnc/ast/Assignable.hxx"

namespace ltn::c::compile {
	struct CompilerInfo {
		const Config & config;
		FxTable & fxTable;
		std::uint64_t & jumpMarkCounter; 
	};

	std::string makeJumpId(const std::string_view name, CompilerInfo & info);


	std::string source(const ast::Source & source, CompilerInfo & info);
	std::string function(const ast::Function & fx, CompilerInfo & info);

	StmtCode statement(const ast::Statement & stmt, CompilerInfo & info, Scope & scope);
	StmtCode ifElse(const ast::IfElse & stmt, CompilerInfo & info, Scope & scope);
	StmtCode whileLoop(const ast::While & stmt, CompilerInfo & info, Scope & scope);
	StmtCode forLoop(const ast::For & stmt, CompilerInfo & info, Scope & scope);
	StmtCode newVar(const ast::NewVar & stmt, CompilerInfo & info, Scope & scope);

	ExprCode expression(const ast::Expression & expr, CompilerInfo & info, Scope & scope);
	ExprCode binary(const ast::Binary & expr, CompilerInfo & info, Scope & scope);
	ExprCode unary(const ast::Unary & expr, CompilerInfo & info, Scope & scope);
	ExprCode primary(const ast::Primary & expr, CompilerInfo & info, Scope & scope);

	ExprCode assignable(const ast::Assignable & expr, CompilerInfo & info, Scope & scope);

	ExprCode addr(const ast::Var & expr, Scope & scope);
}	