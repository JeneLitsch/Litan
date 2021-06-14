#pragma once
#include <stack>
#include "LtncScope.hxx"
#include "LtncFxInfo.hxx"
namespace ltnc {
	class SymbolTable {
	public:
		SymbolTable();

		std::string makeJumpMark(std::string type);

		void insert(const Type & type);
		void insert(const FxSignature & signature);

		const Type & match(const std::string & typeName) const;
		const FxInfo & match(const FxSignature & signature) const;

		bool checkType(const std::string & typeName) const;
		void guardType(const std::string & typeName) const;

		void addBlockScope();
		void addFunctionScope(const FxSignature & signature);
		void remove();
		Scope & get();
	private:
		const Type * find(const std::string & typeName) const;  
		const FxInfo * find(const FxSignature & signature) const; 
		std::vector<Type> types;
		std::vector<FxInfo> fxs;
		std::stack<Scope> scope;
		std::uint64_t jumpmarkCounter;
	};
}