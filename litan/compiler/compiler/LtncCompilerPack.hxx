#pragma once
#include <string>
#include <set>
#include "LtncScopeStack.hxx"
#include "LtncDecl.hxx"
#include "LtncSignature.hxx"
#include "LtncFxInfo.hxx"
namespace ltnc {
	class CompilerPack {
	public:

		CompilerPack();
		std::string makeJumpMark(std::string type);
		void registerFunction(const std::shared_ptr<DeclFunction> & fx);
		std::optional<FxInfo> matchFunction(const FxSignature & signature) const;
		const ScopeStack & getScopes() const;
		ScopeStack & getScopes();

	private:
		std::uint64_t jumpmarkCounter;
		ScopeStack scopeStack;
		std::vector<FxInfo> fxSignatures;
	};
}