#pragma once
#include <span>
#include <cstdint>
#include "Value.hxx"
#include "litan_core/Any.hxx"
#include "VM.hxx"

namespace ltn::vm {
	VM load(std::span<std::uint8_t> bytecode);
	ltn::Any execute(VM & vm, const std::string & function_name, const std::vector<ltn::Any> & arguments);
}