#pragma once
#include <vector>
#include <set>
#include <string>
#include "AddressTable.hxx"
#include "inst/inst.hxx"

namespace ltn::c {
	struct LinkInfo {
		std::set<std::string> external_functions;
		std::set<std::string> internal_functions;
		AddressTable global_table;
		AddressTable member_name_table;
	};
}