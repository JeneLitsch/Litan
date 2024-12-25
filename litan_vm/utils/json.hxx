#pragma once
#include "stdxx/json.hxx"
#include "litan_vm/VMCore.hxx"

namespace ltn::vm {
	Value json_to_value(const stx::json::node & json, VMCore & core);
	stx::json::node value_to_json(const Value & value);
}