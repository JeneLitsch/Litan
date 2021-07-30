#pragma once
#include <stack>
#include "LtncScope.hxx"
#include <variant>
#include "LtncFunction.hxx"
namespace ltnc {

	class SymbolTable {
	public:
		SymbolTable();

		std::string makeJumpMark(const std::string & type);

		TypeId insert(const Type & type);
		FunctionSignature insert(const FunctionSignature & signature);
		VarId insert(const VarId & varId, const TypeId & typeId);

		const Type & match(const TypeId & typeId) const;
		const Function & match(const FunctionSignature & signature, bool perfectFit = true) const;
		const Var & match(const VarId & id) const;

		void addBlockScope();
		void addFunctionScope(const FunctionSignature & signature);
		void remove();

		const FunctionSignature & currentFxSignature() const;
		
	private:
		void add(const auto & entry);
		Scope global;
		std::stack<Scope> scope;
		std::uint64_t jumpmarkCounter;
	};
}