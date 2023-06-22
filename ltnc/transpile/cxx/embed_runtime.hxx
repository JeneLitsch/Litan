#pragma once
#include <ostream>
#include "Indent.hxx"

namespace ltn::c::trans::cxx {
	void embed_runtime(std::ostream &, Indent);
}