#pragma once
#include "decl/Function.hxx"
#include "stmt/Statement.hxx"
#include "expr/Expression.hxx"
#include "expr/Primary.hxx"
#include "expr/Literals.hxx"
#include "expr/Assignable.hxx"

namespace ltn::c::ast {
	using expr_ptr = std::unique_ptr<Expression>;
	using litr_ptr = std::unique_ptr<Literal>;
	using glob_ptr = std::unique_ptr<Global>;
	using prst_ptr = std::unique_ptr<Preset>;
	using stmt_ptr = std::unique_ptr<Statement>;
	using func_ptr = std::unique_ptr<Functional>;
	struct Program {
		std::vector<func_ptr> functions;
		std::vector<glob_ptr> globals;
		std::vector<prst_ptr> presets;
	};
	using prog_ptr = std::unique_ptr<Program>;

	template<typename T>
	concept literal_type = std::is_base_of<ast::Literal, T>::value;
}