#pragma once
#include "ltnc/ast/Ast.hxx"
#include <vector>
#include "stdxx/oop.hxx"
#include "SymbolTable.hxx"

namespace ltn::c {
	struct FunctionTemplateErrors {
		static CompilerError redef(const sst::FunctionTemplate & def) {
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
		= SymbolTable<sst::FunctionTemplate, std::size_t, std::size_t>;
	
	using ValidFunctionTemplateTable
		= ValidSymbolTable<sst::FunctionTemplate, FunctionTemplateErrors, std::size_t, std::size_t>;
	
	using InvalidFunctionTemplateTable
		= InvalidSymbolTable<sst::FunctionTemplate, FunctionTemplateErrors, std::size_t, std::size_t>;
}