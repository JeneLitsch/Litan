#pragma once
#include <string>
#include <set>
#include "LtncDecl.hxx"
#include "LtncCompilerSettings.hxx"
#include "LtncCodeBuffer.hxx"
#include "LtncSymbolTable.hxx"
#include "LtnErrorReporter.hxx"
namespace ltn::c {
	class CompilerPack {
	public:

		CompilerPack(
			const CompilerSettings & settings,
			ltn::ErrorReporter & error);


		
		const SymbolTable & getSymbolTable() const;
		SymbolTable & getSymbolTable();

		const CompilerSettings & getSettings() const;

		CodeBuffer codeBuffer() const;

		ltn::ErrorReporter & error;

	private:
		CompilerSettings settings;
		SymbolTable symbolTable;
	};
}