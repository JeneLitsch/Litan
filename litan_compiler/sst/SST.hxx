#pragma once
#include "types.hxx"
#include "bind/Binding.hxx"
#include "decl/Declaration.hxx"
#include "decl/Definition.hxx"
#include "decl/Function.hxx"
#include "decl/Global.hxx"
#include "expr/Expression.hxx"
#include "stmt/Statement.hxx"
#include "litan_core/file/MemberNameTable.hxx"
#include "litan_core/file/StaticPool.hxx"

namespace ltn::c::sst {
	struct Program {
		std::vector<func_ptr> functions;
		std::vector<defn_ptr> definitions;
		std::vector<glob_ptr> globals;
		MemberNameTable member_name_table;
		StaticPool static_pool;
	};
}