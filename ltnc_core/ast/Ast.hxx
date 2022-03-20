#pragma once
#include "Node.hxx"
#include "Function.hxx"
#include "Expression.hxx"
#include "Primary.hxx"
#include "Statement.hxx"
#include "Literals.hxx"
#include "Assignable.hxx"

namespace ltn::c::ast {
	using expr_ptr = std::unique_ptr<Expression>;
	using litr_ptr = std::unique_ptr<Literal>;
	using glob_ptr = std::unique_ptr<Global>;
	using stmt_ptr = std::unique_ptr<Statement>;
	using func_ptr = std::unique_ptr<Functional>;
	struct Program {
		std::vector<func_ptr> functions;
		std::vector<glob_ptr> globals;
	};
	using prog_ptr = std::unique_ptr<Program>;
}