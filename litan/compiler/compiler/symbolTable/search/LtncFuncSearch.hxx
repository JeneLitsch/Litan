#pragma once
#include <string>
#include "LtncVar.hxx"
#include "LtncType.hxx"
#include "LtncFunction.hxx"

namespace ltnc {
	class SymbolTable;
	class FuncSearch {
	public:
		FuncSearch(const FunctionSignature & signature, const SymbolTable & sTable, bool perfectFit);
		const Func * operator()(const Type & type) const;
		const Func * operator()(const Func & func) const;
		const Func * operator()(const Var & var) const;
	private:
		const FunctionSignature & signature;
		const SymbolTable & sTable;
		bool perfectFit;
	};
}