#pragma once
#include <stack>
#include "LtncScope.hxx"
#include "LtncFxInfo.hxx"
namespace ltnc {
	class SymbolTable {
	public:
		SymbolTable();

		std::string makeJumpMark(std::string type);

		void registerType(const Type & type);
		bool checkType(const std::string & typeName) const;
		void guardType(const std::string & typeName) const;
		const Type & getType(const std::string & typeName) const;

		void addBlockScope();
		void addFunctionScope(const FxSignature & signature);
		void remove();
		Scope & get();

		void registerFunction(const FxSignature & signature);
		std::optional<FxInfo> matchFunction(const FxSignature & signature) const;

	private:
		std::set<Type> types;
		std::stack<Scope> scope;
		std::vector<FxInfo> fxSignatures;
		std::uint64_t jumpmarkCounter;
	};
}