#pragma once
#include "LtncSymbol.hxx"
namespace ltnc {
	struct VarId : public Symbol {
		VarId (const std::string & name) 
			: Symbol(name) {}
	};
}