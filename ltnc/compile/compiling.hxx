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

namespace ltn::c::compile {
	struct CompilerInfo {
		const Config & config;
		Scope & scope;
		FxTable & fxTable;
		std::uint64_t & jumpMarkCounter; 
	};



	std::string source(const ast::Source & source, CompilerInfo & info);
	std::string function(const ast::Function & fx, CompilerInfo & info);

	StmtCode statement(const ast::Statement & stmt, CompilerInfo & info);
	StmtCode ifElse(const ast::IfElse & stmt, CompilerInfo & info);

	ExprCode expression(const ast::Expression & expr, CompilerInfo & info);
	ExprCode binary(const ast::Binary & expr, CompilerInfo & info);
	ExprCode unary(const ast::Unary & expr, CompilerInfo & info);
	ExprCode primary(const ast::Primary & expr, CompilerInfo & info);
}	