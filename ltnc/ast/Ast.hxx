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
	using defn_ptr = std::unique_ptr<Definition>;
	using glob_ptr = std::unique_ptr<Global>;
	using prst_ptr = std::unique_ptr<Preset>;
	using stmt_ptr = std::unique_ptr<Statement>;
	using func_ptr = std::unique_ptr<Functional>;
	using enum_ptr = std::unique_ptr<Enumeration>;
	
	struct Program {
		std::vector<func_ptr> functions;
		std::vector<defn_ptr> definitions;
	};

	struct Source {
		std::vector<func_ptr> functions;
		std::vector<defn_ptr> definitions;
		std::vector<glob_ptr> globals;
		std::vector<prst_ptr> presets;
		std::vector<enum_ptr> enums;
	};


	using prog_ptr = std::unique_ptr<Program>;
	using srce_ptr = std::unique_ptr<Source>;

	template<typename T>
	concept literal_type = std::is_base_of<ast::Literal, T>::value;
}