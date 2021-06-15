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
		std::string insert(const std::string & name, const TypeId & typeId);

		const Type & match(const TypeId & typeId) const;
		const Function & match(const FunctionSignature & signature) const;
		const Var & match(const std::string & name) const;

		void addBlockScope();
		void addFunctionScope(const FunctionSignature & signature);
		void remove();
		Scope & get();
	private:
		Scope global;
		std::stack<Scope> scope;
		std::uint64_t jumpmarkCounter;
	};
}