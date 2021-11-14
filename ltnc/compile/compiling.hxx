#pragma once
#include "ltnc/ast/Expression.hxx"
#include "ltnc/ast/Function.hxx"
#include "ltnc/ast/Source.hxx"
#include "ltnc/ast/Statement.hxx"
#include "ltnc/ast/Node.hxx"

#include "ltnc/Config.hxx"
#include "ltnc/SymbolTable.hxx"

namespace ltn::c::compile {
	std::string source(
		const ast::Source & source,
		const Config & config,
		SymbolTable & stable);
}	