#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "LtncType.hxx"
#include "LtncVar.hxx"
#include "LtncBaseTypes.hxx"
#include "LtncSymbol.hxx"

namespace ltnc {
	class FunctionSignature : public Symbol {
	public:
		FunctionSignature(
			const TypeId & returnType,
			const std::string & name,
			const std::vector<Param> & params,
			const Namespace & ns = Namespace())
		:	Symbol(name, ns),
			returnType(returnType),
			params(params) {}

		TypeId returnType;
		std::vector<Param> params;
	};
};
