#pragma once
#include "Function.hxx"
#include "Statement.hxx"
#include "Statements.hxx"
#include "Expression.hxx"
#include "Expressions.hxx"
#include "Binding.hxx"

namespace ltn::c::sst {
	using defn_ptr = std::unique_ptr<Definition>;
	using glob_ptr = std::unique_ptr<Global>;
	using func_ptr = std::unique_ptr<Functional>;
	using bind_ptr = std::unique_ptr<Binding>;
	
	struct Program {
		std::vector<func_ptr> functions;
		std::vector<defn_ptr> definitions;
		std::vector<glob_ptr> globals;
	};
	template<typename T>
	concept literal_type = std::is_base_of<sst::Literal, T>::value;
}