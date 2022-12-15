#pragma once
#include "ltnc/ast/AST.hxx"
#include <vector>
#include "stdxx/oop.hxx"
#include "SymbolTable.hxx"

namespace ltn::c {
	struct DefinitionErrors {
		static CompilerError redef(const sst::Definition & def) {
			std::stringstream msg;
			msg << "Definition ";
			msg << def.namespaze.to_string();
			msg << def.name;
			msg	<< " already exists";
			return CompilerError{ msg.str(), {} };
		}

		
		static CompilerError decl(const std::string & inside) {
			return CompilerError {
				"Cannot declare definition inside a " + inside
			};
		}
		
		static CompilerError use(const std::string & inside) {
			return CompilerError {
				"Cannot use definition inside a " + inside
			};
		}
	};

	using DefinitionTable
		= SymbolTable<sst::Definition>;
	
	using ValidDefinitionTable
		= ValidSymbolTable<sst::Definition, DefinitionErrors>;
	
	using InvalidDefinitionTable
		= InvalidSymbolTable<sst::Definition, DefinitionErrors>;
}