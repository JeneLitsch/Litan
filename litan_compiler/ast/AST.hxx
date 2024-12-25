#pragma once
#include "litan_compiler/ast/bind/Binding.hxx"
#include "litan_compiler/ast/decl/Enumeration.hxx"
#include "litan_compiler/ast/decl/Declaration.hxx"
#include "litan_compiler/ast/decl/Definition.hxx"
#include "litan_compiler/ast/decl/Global.hxx"
#include "litan_compiler/ast/decl/Function.hxx"
#include "litan_compiler/ast/expr/Expression.hxx"
#include "litan_compiler/ast/stmt/Statement.hxx"
#include "types.hxx"

namespace ltn::c::ast {
	struct Program {
		std::vector<func_ptr> functions;
		std::vector<defn_ptr> definitions;
		std::vector<glob_ptr> globals;
		std::vector<enum_ptr> enums;
	};

	Program & operator+=(Program & ast, Program addition);
}