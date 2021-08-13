#pragma once
#include <string>
#include "LtncVar.hxx"
#include "LtncType.hxx"
#include "LtncFunction.hxx"
#include "Unused.hxx"
namespace ltn::c {
	class VarSearch {
	public:
		VarSearch(const std::string & name);
		
		const Var * operator()(const Type & type) const;
		const Var * operator()(const Function & func) const;
		const Var * operator()(const Var & var) const;
	private:
		std::string name;
	};
}