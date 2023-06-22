#pragma once
#include <ostream>
#include <string_view>
#include "Indent.hxx"

namespace ltn::c::trans::cxx {
	void print_arith_dispatch(std::ostream & stream, Indent indent, std::string_view name);
	void print_wrapped_operator(std::ostream & stream, Indent indent, std::string_view name, std::string_view op);
}