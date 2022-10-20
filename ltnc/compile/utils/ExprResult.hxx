#pragma once
#include <string>
#include "InstructionBuffer.hxx"
#include "ltnc/type/Type.hxx"

namespace ltn::c {
	struct ExprResult {
		InstructionBuffer code;
		type::Type deduced_type = type::Any{};
	};
}