#pragma once
#include <string>
#include "LtncVar.hxx"
#include "LtncType.hxx"
#include "LtncFunction.hxx"
#include "Unused.hxx"
namespace ltnc {
	class VarSearch {
	public:
		VarSearch(const std::string & name)
			: name(name) {}
		
		const Var * operator()(const Type & type) const {
			UNUSED(type);
			return nullptr;
		}

		const Var * operator()(const Func & func) const {
			UNUSED(func);
			return nullptr;
		}

		const Var * operator()(const Var & var) const {
			if(name == var.name) {
				return &var;
			}
			return nullptr;
		}

	private:
		std::string name;
	};
}