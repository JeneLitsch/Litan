#pragma once
#include <string>
#include <set>
#include "LtncDecl.hxx"
#include "LtncCompilerSettings.hxx"
#include "LtncCodeBuffer.hxx"
#include "LtncSymbolTable.hxx"
namespace ltnc {
	class CompilerPack {
	public:

		CompilerPack(const CompilerSettings & settings);


		
		const SymbolTable & getSymbolTable() const;
		SymbolTable & getSymbolTable();

		const CompilerSettings & getSettings() const;

		CodeBuffer codeBuffer() const;

	private:
		CompilerSettings settings;
		SymbolTable symbolTable;
	};
}