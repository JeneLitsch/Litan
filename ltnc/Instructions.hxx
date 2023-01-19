#pragma once
#include <vector>
#include <set>
#include <string>
#include "AddressTable.hxx"
#include "inst/inst.hxx"

namespace ltn::c {
	struct LinkInfo {
		std::set<std::string> init_functions;
		AddressTable global_table;
	};
}