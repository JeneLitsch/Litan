#pragma once
#include <unordered_map>
#include <cstdint>
#include <string>
#include "ltnc/ast/Ast.hxx"
#include "stdxx/oop.hxx"

namespace ltn::c {
	struct GlobalErrors {
		static CompilerError redef(const ast::Global & def) {
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
		= SymbolTable<ast::Global>;
	
	using ValidGlobalTable
		= ValidSymbolTable<ast::Global, GlobalErrors>;
	
	using InvalidGlobalTable
		= InvalidSymbolTable<ast::Global, GlobalErrors>;
}