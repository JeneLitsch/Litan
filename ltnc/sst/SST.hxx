#pragma once
#include "Function.hxx"
#include "Statement.hxx"
#include "Expression.hxx"
#include "Type.hxx"

namespace ltn::c::sst {
	using expr_ptr = std::unique_ptr<Expression>;
	using litr_ptr = std::unique_ptr<Literal>;
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
	};

	struct Source {
		std::vector<func_ptr> functions;
		std::vector<ftmp_ptr> function_templates;
		std::vector<defn_ptr> definitions;
		std::vector<glob_ptr> globals;
		std::vector<prst_ptr> presets;
		std::vector<enum_ptr> enums;
	};


	using prog_ptr = std::unique_ptr<Program>;
	using srce_ptr = std::unique_ptr<Source>;

	template<typename T>
	concept literal_type = std::is_base_of<sst::Literal, T>::value;
}