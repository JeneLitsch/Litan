#pragma once
#include <sstream>
#include <span>
#include <atomic>
#include "ltn/casts.hxx"
#include "ltn/unique.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/Reporter.hxx"
#include "ltnc/ast/Ast.hxx"
#include "FunctionTable.hxx"
#include "FunctionTemplateTable.hxx"
#include "DefinitionTable.hxx"
#include "MemberTable.hxx"
#include "GlobalTable.hxx"
#include "Scope.hxx"
#include "stdxx/oop.hxx"
#include "FunctionQueue.hxx"

namespace ltn::c {
	struct CompilerInfo {
		FunctionTable & fx_table;
		FunctionTemplateTable & fx_template_table;
		FunctionQueue & fx_queue;
		DefinitionTable & definition_table;
		MemberTable & member_table;
		GlobalTable & global_table;
		Reporter & reporter;
	};

	std::string make_jump_id(const std::string_view name);
}	