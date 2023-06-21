#pragma once
#include <string_view>
#include "ltnc/sst/SST.hxx"
#include "Indent.hxx"

namespace ltn::c::trans::cxx {
	void print_function_header(const sst::Functional &, std::ostream &);
	void print_namespace(const Namespace &, std::ostream &);

	void print_delete_special_members(std::ostream &, std::string_view name, Indent);
}