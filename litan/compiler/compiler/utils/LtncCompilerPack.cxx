#include "LtncCompilerPack.hxx"
#include <iostream>
ltn::c::CompilerPack::CompilerPack(
	const CompilerSettings & settings,
	ltn::ErrorReporter & error) 
	: error(error), settings(settings) {
}

const ltn::c::SymbolTable & ltn::c::CompilerPack::getSymbolTable() const {
	return this->symbolTable;
}

ltn::c::SymbolTable & ltn::c::CompilerPack::getSymbolTable(){
	return this->symbolTable;
}


const ltn::c::CompilerSettings & ltn::c::CompilerPack::getSettings() const {
	return this->settings;
}

ltn::c::CodeBuffer ltn::c::CompilerPack::codeBuffer() const {
	return CodeBuffer(this->settings.areCommentsActive());
}