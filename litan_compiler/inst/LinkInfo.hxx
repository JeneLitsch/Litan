#pragma once
#include "litan_compiler/AddressTable.hxx"
#include "litan_core/file/FunctionPool.hxx"
#include "litan_core/file/MemberNameTable.hxx"
#include "litan_core/file/StringPool.hxx"

namespace ltn::c {
	struct LinkInfo {
		MemberNameTable member_name_table;
		AddressTable jump_table;
		FunctionPool function_pool;
		StringPool string_pool;
	};
}