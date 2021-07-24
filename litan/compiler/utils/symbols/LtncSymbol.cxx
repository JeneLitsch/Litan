#include "LtncSymbol.hxx"

ltnc::Symbol::Symbol(const std::string & name) 
	: name(name) {}

ltnc::Symbol::Symbol(const std::string & name, const Namespace & ns) 
	: name(name), ns(ns) {}