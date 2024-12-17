#pragma once
#include "ltnc/AddressTable.hxx"
#include "ltn/file/FunctionPool.hxx"
#include "ltn/file/StringPool.hxx"

namespace ltn::c {
	struct LinkInfo {
		AddressTable member_name_table;
		AddressTable jump_table;
		FunctionPool function_pool;
		StringPool string_pool;
	};
}