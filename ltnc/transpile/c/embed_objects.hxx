#pragma once
#include <ostream>
#include "Indent.hxx"

namespace ltn::c::trans::cxx {
	void embed_object(std::ostream & out, std::string_view name, std::string_view wrapped, Indent indent);
}