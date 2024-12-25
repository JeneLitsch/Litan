#pragma once
#include <string_view>
#include <string>
#include <vector>
#include <span>
#include <array>
#include "litan_compiler/inst/inst.hxx"

namespace ltn::c {
	inst::Inst resolve_build_in(const std::string_view & key);
}