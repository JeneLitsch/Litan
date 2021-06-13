#pragma once
#include <string>
#include <set>
#include "LtncScopeStack.hxx"
#include "LtncDecl.hxx"
#include "LtncSignature.hxx"
#include "LtncFxInfo.hxx"
#include "LtncCompilerSettings.hxx"
#include "LtncTypeTable.hxx"
#include "LtncCodeBuffer.hxx"
namespace ltnc {
	class CompilerPack {
	public:

		CompilerPack(const CompilerSettings & settings);
		std::string makeJumpMark(std::string type);

		void registerFunction(
			const std::shared_ptr<DeclFunction> & fx);
		
		std::optional<FxInfo> matchFunction(
			const FxSignature & signature) const;
		
		void addInlineCode(
			const FxSignature & signature,
			const std::string & code);

		const ScopeStack & getScopes() const;
		ScopeStack & getScopes();

		const TypeTable & getTypeTable() const;
		TypeTable & getTypeTable();

		const CompilerSettings & getSettings() const;

		CodeBuffer codeBuffer() const;

	private:
		std::uint64_t jumpmarkCounter;
		ScopeStack scopeStack;
		std::vector<FxInfo> fxSignatures;
		CompilerSettings settings;
		TypeTable typeTable;
	};
}