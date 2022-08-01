#pragma once
#include "ltnc/ast/Ast.hxx"
#include <vector>
#include "stdxx/oop.hxx"
#include "SymbolTable.hxx"

namespace ltn::c {
	struct FunctionsErrors {
		static CompilerError redef(const ast::Functional & def) {
			std::stringstream msg;
			msg << "Function ";
			msg << def.namespaze.to_string();
			msg << def.name;
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
		= SymbolTable<ast::Functional, std::size_t>;
	
	using ValidFunctionTable
		= ValidSymbolTable<ast::Functional, FunctionsErrors, std::size_t>;
	
	using InvalidFunctionTable
		= InvalidSymbolTable<ast::Functional, FunctionsErrors, std::size_t>;
}