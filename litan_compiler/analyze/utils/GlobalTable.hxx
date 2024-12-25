#pragma once
#include <unordered_map>
#include <cstdint>
#include <string>
#include "stdxx/oop.hxx"
#include "SymbolTable.hxx"
#include "litan_compiler/sst/SST.hxx"
#include "litan_compiler/CompilerError.hxx"

namespace ltn::c {
	struct GlobalErrors {
		static CompilerError redef(const sst::decl::Global & def);
		static CompilerError decl(const std::string & inside);
		static CompilerError use(const std::string & inside);
	};

	using GlobalTable
		= SymbolTable<sst::decl::Global>;
	
	using ValidGlobalTable
		= ValidSymbolTable<sst::decl::Global, GlobalErrors>;
	
	using InvalidGlobalTable
		= InvalidSymbolTable<sst::decl::Global, GlobalErrors>;
}