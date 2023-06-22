#pragma once
#include <ostream>
#include <array>
#include <vector>
#include <string_view>
#include "Indent.hxx"

namespace ltn::c::trans::cxx {
	void binary_dispatch(std::ostream & out, Indent indent, std::string_view name,
		const std::vector<std::array<std::string, 4>> & operands);

	void arith_dispatch(std::ostream &, Indent, std::string_view name);
	void add_dispatch(std::ostream &, Indent);
	
	void wrap_binary_operator(std::ostream &, Indent, std::string_view name, std::string_view op);
	void print_concat(std::ostream &, Indent);

	void unary_dispatch(std::ostream &, std::string_view name, Indent indent);
	void wrap_unary_operator(std::ostream &, Indent, std::string_view name, std::string_view op);
}