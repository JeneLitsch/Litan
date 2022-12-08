#pragma once
#include "ltnc/ast/Ast.hxx"
#include <vector>
#include "stdxx/oop.hxx"
#include "SymbolTable.hxx"

namespace ltn::c {
	struct FunctionTemplateErrors {
		static CompilerError redef(const ast::FunctionTemplate & def) {
			std::stringstream msg;
			msg << "Function template";
			msg << def.get_resolve_namespace().to_string();
			msg << def.get_resolve_name();
			msg	<< " already exists";
			return CompilerError{ msg.str(), {} };
		}

		
		static CompilerError decl(const std::string & inside) {
			return CompilerError {
				"Cannot declare function template inside a " + inside
			};
		}
		
		static CompilerError use(const std::string & inside) {
			return CompilerError {
				"Cannot use function template inside a " + inside
			};
		}
	};

	using FunctionTemplateTable
		= SymbolTable<ast::FunctionTemplate, std::size_t, std::size_t>;
	
	using ValidFunctionTemplateTable
		= ValidSymbolTable<ast::FunctionTemplate, FunctionTemplateErrors, std::size_t, std::size_t>;
	
	using InvalidFunctionTemplateTable
		= InvalidSymbolTable<ast::FunctionTemplate, FunctionTemplateErrors, std::size_t, std::size_t>;
}