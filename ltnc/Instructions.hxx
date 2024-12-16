#pragma once
#include <vector>
#include <set>
#include <string>
#include "AddressTable.hxx"
#include "ltn/file/FunctionPool.hxx"
#include "ltn/file/StringPool.hxx"
#include "inst/inst.hxx"

namespace ltn::c {
	struct LinkInfo {
		AddressTable global_table;
		AddressTable member_name_table;
		AddressTable jump_table;
		FunctionPool function_pool;
		StringPool string_pool;
	};
}