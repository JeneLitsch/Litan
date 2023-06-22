#pragma once
#include <ostream>
#include "Indent.hxx"

namespace ltn::c::trans::cxx {
	void embed_sweep(std::ostream &, Indent);
	void embed_mark(std::ostream &, Indent);
	void embed_run_gc(std::ostream & , Indent);
}