#pragma once
#include <ostream>
#include "Indent.hxx"

namespace ltn::c::trans::cxx {
	void invalid_operands(std::ostream & out, Indent indent);
}