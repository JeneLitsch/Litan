#pragma once
#include <sstream>
#include <span>
#include <atomic>
#include "ltn/casts.hxx"
#include "ltn/unique.hxx"
#include "ltnc/Config.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/Reporter.hxx"
#include "ltnc/ast/Ast.hxx"
#include "FxTable.hxx"
#include "GlobalTable.hxx"
#include "MemberTable.hxx"
#include "Scope.hxx"

namespace ltn::c::compile {
	struct CompilerInfo {
		const Config & config;
		FxTable & fx_table;
		GlobalTable & global_table;
		MemberTable & member_table;
		Reporter & reporter;
	};

	std::string make_jump_id(const std::string_view name);
}	