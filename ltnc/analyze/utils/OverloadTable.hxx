#pragma once
#include "ltnc/ast/AST.hxx"
#include "ltnc/sst/SST.hxx"
#include <vector>
#include "stdxx/oop.hxx"
#include "SymbolTable.hxx"

namespace ltn::c {
	struct OverloadErrors {
		static CompilerError redef(const ast::Overload & overload) {
			std::stringstream msg;
			msg << "Function ";
			msg << overload.get_resolve_namespace().to_string();
			msg << overload.get_resolve_name();
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

	using OverloadTable
		= SymbolTable<ast::Overload, std::size_t>;
	
	using ValidOverloadTable
		= ValidSymbolTable<ast::Overload, OverloadErrors, std::size_t>;
	
	using InvalidOverloadTable
		= InvalidSymbolTable<ast::Overload, OverloadErrors, std::size_t>;
}