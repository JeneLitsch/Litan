#pragma once
#include "litan_vm/Value.hxx"

namespace ltn::vm {
	Value get_element_from_container(Value container, Value key);
}