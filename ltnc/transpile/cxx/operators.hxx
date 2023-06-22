#pragma once
#include <ostream>
#include <string_view>
#include "Indent.hxx"

namespace ltn::c::trans::cxx {
	void arith_dispatch(std::ostream & stream, Indent indent, std::string_view name);
	void wrap_binary_operator(std::ostream & stream, Indent indent, std::string_view name, std::string_view op);

	void unary_dispatch(std::ostream & stream, std::string_view name, Indent indent);
	void wrap_unary_operator(std::ostream & stream, Indent indent, std::string_view name, std::string_view op);
}