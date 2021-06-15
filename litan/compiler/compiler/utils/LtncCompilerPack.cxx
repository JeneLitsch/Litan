#include "LtncCompilerPack.hxx"
#include <iostream>
ltnc::CompilerPack::CompilerPack(const CompilerSettings & settings) 
	: settings(settings) {
}

const ltnc::SymbolTable & ltnc::CompilerPack::getSymbolTable() const {
	return this->symbolTable;
}

ltnc::SymbolTable & ltnc::CompilerPack::getSymbolTable(){
	return this->symbolTable;
}


const ltnc::CompilerSettings & ltnc::CompilerPack::getSettings() const {
	return this->settings;
}

ltnc::CodeBuffer ltnc::CompilerPack::codeBuffer() const {
	return CodeBuffer(this->settings.areCommentsActive());
}