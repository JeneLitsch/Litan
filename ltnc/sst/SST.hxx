#pragma once
#include "bind/Binding.hxx"
#include "decl/Declaration.hxx"
#include "decl/Function.hxx"
#include "expr/Expression.hxx"
#include "expr/Expressions.hxx"
#include "stmt/Statement.hxx"
#include "stmt/Statements.hxx"
#include "ltnc/AddressTable.hxx"

namespace ltn::c::sst {
	using defn_ptr = std::unique_ptr<Definition>;
	using glob_ptr = std::unique_ptr<Global>;
	using func_ptr = std::unique_ptr<Functional>;
	using bind_ptr = std::unique_ptr<Binding>;
	
	struct Program {
		std::vector<func_ptr> functions;
		std::vector<defn_ptr> definitions;
		std::vector<glob_ptr> globals;
		AddressTable member_name_table;
	};
	template<typename T>
	concept literal_type = std::is_base_of<sst::Literal, T>::value;
}