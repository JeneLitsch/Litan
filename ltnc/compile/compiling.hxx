#pragma once
#include "Scope.hxx"
#include "FxTable.hxx"

#include "ltnc/Config.hxx"

#include "ltnc/ast/Expression.hxx"
#include "ltnc/ast/Function.hxx"
#include "ltnc/ast/Source.hxx"
#include "ltnc/ast/Statement.hxx"
#include "ltnc/ast/Node.hxx"
#include "ltnc/type/Primitives.hxx"
#include "ltnc/type/Type.hxx"

namespace ltn::c::compile {
	struct CompilerInfo {
		const Config & config;
		Scope & scope;
		FxTable & fxTable;
		std::uint64_t & jumpMarkCounter; 
	};



	std::string source(const ast::Source & source, CompilerInfo & info);
	std::string function(const ast::Function & function, CompilerInfo & info);
}	