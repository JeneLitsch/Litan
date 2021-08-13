#pragma once
#include <string>
#include "LtncVar.hxx"
#include "LtncType.hxx"
#include "LtncFunction.hxx"
namespace ltn::c {
	class TypeSearch {
	public:
		TypeSearch(const TypeId & typeId);
		const Type * operator()(const Type & type) const;
		const Type * operator()(const Function & func) const;
		const Type * operator()(const Var & var) const;
	private:
		TypeId typeId;
	};
}