#pragma once
#include <sstream>
#include <span>
#include <atomic>
#include "stdxx/oop.hxx"

#include "ltn/casts.hxx"
#include "ltn/unique.hxx"

#include "ltnc/CompilerError.hxx"
#include "ltnc/Reporter.hxx"
#include "ltnc/ast/AST.hxx"

#include "FunctionTable.hxx"
#include "FunctionTemplateTable.hxx"
#include "DefinitionTable.hxx"
#include "MemberTable.hxx"
#include "GlobalTable.hxx"
#include "OverloadTable.hxx"

#include "Scope.hxx"
#include "FunctionQueue.hxx"

namespace ltn::c {
	struct Context {
		FunctionTable & fx_table;
		FunctionTemplateTable & fx_template_table;
		FunctionQueue & fx_queue;
		OverloadTable & overload_table;
		DefinitionTable & definition_table;
		MemberTable & member_table;
		GlobalTable & global_table;
		Reporter & reporter;
	};

}	