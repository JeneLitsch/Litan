#pragma once
#include <string_view>
#include <functional>
#include "ltnc/sst/SST.hxx"
#include "Indent.hxx"

namespace ltn::c::trans::cxx {
	using Print = std::function<void(std::ostream &, Indent)>;

	void print_function_header(const sst::Functional &, std::ostream &);
	void print_namespace(const Namespace &, std::ostream &);
	void print_delete_special_members(std::ostream &, std::string_view name, Indent);
	void print_object_wrapper(std::ostream &, std::string_view name, std::string_view wrapped, Indent);

	void print_switch(std::ostream & out, Indent indent, std::string_view expr, const std::map<std::string, Print> & cases);
}