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


		
		void addInlineCode(
			const FxSignature & signature,
			const std::string & code);

		const SymbolTable & getSymbolTable() const;
		SymbolTable & getSymbolTable();

		const CompilerSettings & getSettings() const;

		CodeBuffer codeBuffer() const;

	private:
		CompilerSettings settings;
		SymbolTable symbolTable;
	};
}