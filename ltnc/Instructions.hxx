#pragma once
#include <vector>
#include <set>
#include <string>
#include "AddressTable.hxx"
#include "ltn/file/FunctionTable.hxx"
#include "inst/inst.hxx"

namespace ltn::c {
	struct LinkInfo {
		AddressTable global_table;
		AddressTable member_name_table;
		AddressTable jump_table;
		ltn::FunctionTable function_table;
	};
}