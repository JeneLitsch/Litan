#pragma once
#include "ltnc/ast/bind/Binding.hxx"
#include "ltnc/ast/decl/Enumeration.hxx"
#include "ltnc/ast/decl/Declaration.hxx"
#include "ltnc/ast/decl/Definition.hxx"
#include "ltnc/ast/decl/Global.hxx"
#include "ltnc/ast/decl/Function.hxx"
#include "ltnc/ast/expr/Expression.hxx"
#include "ltnc/ast/stmt/Statement.hxx"
#include "types.hxx"

namespace ltn::c::ast {
	struct Program {
		std::vector<func_ptr> functions;
		std::vector<defn_ptr> definitions;
		std::vector<glob_ptr> globals;
		std::vector<enum_ptr> enums;
	};
}