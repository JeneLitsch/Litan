#pragma once
#include "LtncSymbol.hxx"
namespace ltn::c {
	struct VarId : public Symbol {
		VarId (const std::string & name) 
			: Symbol(name) {}
	};

	std::ostream & operator<<(std::ostream & stream, const VarId & varId);
}