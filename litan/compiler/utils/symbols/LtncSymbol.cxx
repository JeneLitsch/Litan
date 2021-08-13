#include "LtncSymbol.hxx"

ltn::c::Symbol::Symbol(const std::string & name) 
	: name(name) {}

ltn::c::Symbol::Symbol(const std::string & name, const Namespace & ns) 
	: name(name), ns(ns) {}