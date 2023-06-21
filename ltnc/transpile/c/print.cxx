#include "print.hxx"

namespace ltn::c::trans::cxx {
	void print_function_header(const sst::Functional & fx, std::ostream & out) {
		out << "ltn::Value " << fx.name << "_" << fx.arity() << "(";
		for(std::size_t i = 0; i < fx.arity(); i++) {
			if(i) out << ",";
			out << "ltn::Value var_" << i;
		}
		out << ")";
	}
}