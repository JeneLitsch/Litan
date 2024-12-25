#pragma once
#include "litan_compiler/ast/AST.hxx"
#include "litan_compiler/sst/SST.hxx"
#include <vector>
#include "stdxx/oop.hxx"
#include "SymbolTable.hxx"

namespace ltn::c {

	struct FunctionErrors {
		static CompilerError redef(const ast::decl::Function & def) {
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
		= SymbolTable<ast::decl::Function, std::size_t, VariadicMode>;
	
	using ValidFunctionTable
		= ValidSymbolTable<ast::decl::Function, FunctionErrors, std::size_t, VariadicMode>;
	
	using InvalidFunctionTable
		= InvalidSymbolTable<ast::decl::Function, FunctionErrors, std::size_t, VariadicMode>;
}