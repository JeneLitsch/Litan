#pragma once
#include <string>
#include <set>
#include "LtncDecl.hxx"
#include "LtncSignature.hxx"
#include "LtncFxInfo.hxx"
#include "LtncCompilerSettings.hxx"
#include "LtncCodeBuffer.hxx"
#include "LtncSymbolTable.hxx"
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

		const SymbolTable & getSymbolTable() const;
		SymbolTable & getSymbolTable();

		const CompilerSettings & getSettings() const;

		CodeBuffer codeBuffer() const;

	private:
		std::uint64_t jumpmarkCounter;
		std::vector<FxInfo> fxSignatures;
		CompilerSettings settings;
		SymbolTable symbolTable;
	};
}