#pragma once
#include "LtncFunction.hxx"
#include "LtncType.hxx"
#include "LtncVar.hxx"
namespace ltnc {
	struct DumpTable {
		void operator()(const Type & type) const {
			std::cout << "Type: " << type.id.name << std::endl;
		}

		void operator()(const Func & func) const {
			std::cout << "Func: " << func.signature.name << std::endl;
		}

		void operator()(const Var & var) const {
			std::cout << "Var: \"" << var.name << "\"" << std::endl;
		}
	};
}