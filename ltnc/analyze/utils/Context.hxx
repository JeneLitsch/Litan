#pragma once
#include <sstream>
#include <span>
#include <atomic>
#include "ltn/casts.hxx"
#include "ltn/unique.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/ast/AST.hxx"
#include "FunctionTable.hxx"

#include "CustomResolver.hxx"
#include "DefinitionTable.hxx"
#include "GlobalTable.hxx"
#include "stdxx/oop.hxx"
#include "FunctionQueue.hxx"

namespace ltn::c {
	struct Context {
		FunctionTable & fx_table;
		FunctionQueue & fx_queue;
		DefinitionTable & definition_table;
		GlobalTable & global_table;
		CustomResolver & custom_resolver;
	};

}	