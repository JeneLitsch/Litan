#pragma once
#include "Node.hxx"
#include "Function.hxx"
#include "Expression.hxx"
#include "Statement.hxx"
#include "Literals.hxx"
#include "Assignable.hxx"

namespace ltn::c::ast {
	using expr_ptr = std::unique_ptr<Expression>;
	using stmt_ptr = std::unique_ptr<Statement>;
	using func_ptr = std::unique_ptr<Functional>;
	using enum_ptr = std::unique_ptr<Enum>;
	struct Program {
		std::vector<func_ptr> functions;
	};
	using prog_ptr = std::unique_ptr<Program>;
}