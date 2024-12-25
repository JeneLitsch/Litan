#pragma once
#include <vector>
#include "stdxx/oop.hxx"
#include "SymbolTable.hxx"
#include "litan_compiler/sst/SST.hxx"
#include "litan_compiler/CompilerError.hxx"

namespace ltn::c {
	struct DefinitionErrors {
		static CompilerError redef(const sst::decl::Definition & def);
		static CompilerError decl(const std::string & inside);
		static CompilerError use(const std::string & inside);
	};

	using DefinitionTable
		= SymbolTable<sst::decl::Definition>;
	
	using ValidDefinitionTable
		= ValidSymbolTable<sst::decl::Definition, DefinitionErrors>;
	
	using InvalidDefinitionTable
		= InvalidSymbolTable<sst::decl::Definition, DefinitionErrors>;
}