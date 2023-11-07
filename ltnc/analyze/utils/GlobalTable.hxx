#pragma once
#include <unordered_map>
#include <cstdint>
#include <string>
#include "stdxx/oop.hxx"
#include "SymbolTable.hxx"
#include "ltnc/sst/SST.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	struct GlobalErrors {
		static CompilerError redef(const sst::Global & def);
		static CompilerError decl(const std::string & inside);
		static CompilerError use(const std::string & inside);
	};

	using GlobalTable
		= SymbolTable<sst::Global>;
	
	using ValidGlobalTable
		= ValidSymbolTable<sst::Global, GlobalErrors>;
	
	using InvalidGlobalTable
		= InvalidSymbolTable<sst::Global, GlobalErrors>;
}