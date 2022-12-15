#pragma once
#include <unordered_map>
#include <cstdint>
#include <string>
#include "ltnc/ast/AST.hxx"
#include "stdxx/oop.hxx"

namespace ltn::c {
	struct GlobalErrors {
		static CompilerError redef(const sst::Global & def) {
			std::stringstream msg;
			msg << "Global variable ";
			msg << def.namespaze.to_string();
			msg << def.name;
			msg	<< " already exists";
			return CompilerError{ msg.str(), {} };
		}

		
		static CompilerError decl(const std::string & inside) {
			return CompilerError {
				"Cannot declare globals inside " + inside
			};
		}
		
		static CompilerError use(const std::string & inside) {
			return CompilerError {
				"Cannot use globals inside " + inside
			};
		}
	};

	using GlobalTable
		= SymbolTable<sst::Global>;
	
	using ValidGlobalTable
		= ValidSymbolTable<sst::Global, GlobalErrors>;
	
	using InvalidGlobalTable
		= InvalidSymbolTable<sst::Global, GlobalErrors>;
}