#pragma once
#include <string_view>
#include "ltnc/sst/SST.hxx"
#include "Indent.hxx"

namespace ltn::c::trans::cxx {
	void print_function_header(const sst::Functional &, std::ostream &);
	void print_namespace(const Namespace &, std::ostream &);
	void print_delete_special_members(std::ostream &, std::string_view name, Indent);
	void print_object_wrapper(std::ostream &, std::string_view name, std::string_view wrapped, Indent);
	void print_sweep(std::ostream &, Indent);
}