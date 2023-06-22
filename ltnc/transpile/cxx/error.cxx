#include "error.hxx"

namespace ltn::c::trans::cxx {
	void invalid_operands(std::ostream & out, Indent indent) {
		out << indent << "throw std::runtime_error(\"Invalid operands\");\n";  
	}
}