#pragma once
#include "Function.hxx"
#include "Statement.hxx"
#include "Expression.hxx"

namespace ltn::c::ast {
	using expr_ptr = std::unique_ptr<Expression>;
	using defn_ptr = std::unique_ptr<Definition>;
	using glob_ptr = std::unique_ptr<Global>;
	using prst_ptr = std::unique_ptr<Preset>;
	using stmt_ptr = std::unique_ptr<Statement>;
	using func_ptr = std::unique_ptr<Functional>;
	using ftmp_ptr = std::unique_ptr<FunctionTemplate>;
	using enum_ptr = std::unique_ptr<Enumeration>;
	
	struct Program {
		std::vector<func_ptr> functions;
		std::vector<ftmp_ptr> function_templates;
		std::vector<defn_ptr> definitions;
		std::vector<glob_ptr> globals;
		std::vector<prst_ptr> presets;
		std::vector<enum_ptr> enums;
	};
}