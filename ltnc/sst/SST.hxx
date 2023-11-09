#pragma once
#include "bind/Binding.hxx"
#include "decl/Declaration.hxx"
#include "decl/Definition.hxx"
#include "decl/Function.hxx"
#include "decl/Global.hxx"
#include "expr/Expression.hxx"
#include "stmt/Statement.hxx"
#include "ltnc/AddressTable.hxx"

namespace ltn::c::sst {
	using expr_ptr = expr::expr_ptr;
	using defn_ptr = std::unique_ptr<Definition>;
	using glob_ptr = std::unique_ptr<Global>;
	using func_ptr = std::unique_ptr<Function>;
	using bind_ptr = std::unique_ptr<bind::Binding>;
	
	struct Program {
		std::vector<func_ptr> functions;
		std::vector<defn_ptr> definitions;
		std::vector<glob_ptr> globals;
		AddressTable member_name_table;
	};

}