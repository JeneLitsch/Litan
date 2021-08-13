#pragma once
#include <string>
#include "LtncVar.hxx"
#include "LtncType.hxx"
#include "LtncFunction.hxx"

namespace ltn::c {
	class SymbolTable;
	class FuncSearch {
	public:
		FuncSearch(const FunctionSignature & signature, const SymbolTable & sTable, bool perfectFit);
		const Function * operator()(const Type & type) const;
		const Function * operator()(const Function & func) const;
		const Function * operator()(const Var & var) const;
	private:
		const FunctionSignature & signature;
		const SymbolTable & sTable;
		bool perfectFit;
	};
}