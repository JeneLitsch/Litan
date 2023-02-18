#pragma once
#include "ltnc/ast/AST.hxx"
#include "ltnc/sst/SST.hxx"
#include <vector>
#include "stdxx/oop.hxx"
#include "SymbolTable.hxx"

namespace ltn::c {
	struct FunctionErrors {
		static CompilerError redef(const ast::Functional & def) {
			std::stringstream msg;
			msg << "Function";
			msg << def.get_resolve_namespace().to_string();
			msg << def.get_resolve_name();
			msg	<< " already exists";
			return CompilerError{ msg.str(), {} };
		}

		
		static CompilerError decl(const std::string & inside) {
			return CompilerError {
				"Cannot declare function inside a " + inside
			};
		}
		
		static CompilerError use(const std::string & inside) {
			return CompilerError {
				"Cannot use function inside a " + inside
			};
		}
	};

	using FunctionTable
		= SymbolTable<ast::Functional, std::size_t, std::size_t>;
	
	using ValidFunctionTable
		= ValidSymbolTable<ast::Functional, FunctionErrors, std::size_t, std::size_t>;
	
	using InvalidFunctionTable
		= InvalidSymbolTable<ast::Functional, FunctionErrors, std::size_t, std::size_t>;
}