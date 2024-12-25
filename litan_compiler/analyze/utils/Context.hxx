#pragma once
#include <sstream>
#include <span>
#include <atomic>
#include "litan_core/casts.hxx"
#include "litan_core/unique.hxx"
#include "litan_compiler/CompilerError.hxx"
#include "litan_compiler/ast/AST.hxx"
#include "FunctionTable.hxx"

#include "CustomResolver.hxx"
#include "DefinitionTable.hxx"
#include "MemberTable.hxx"
#include "GlobalTable.hxx"
#include "stdxx/oop.hxx"
#include "FunctionQueue.hxx"

namespace ltn::c {
	struct Context {
		FunctionTable & fx_table;
		FunctionQueue & fx_queue;
		DefinitionTable & definition_table;
		MemberTable & member_table;
		GlobalTable & global_table;
		CustomResolver & custom_resolver;
	};

}	