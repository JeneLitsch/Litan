#pragma once
#include "ltnc/inst/inst.hxx"
#include "ltnc/Instructions.hxx"
#include "scan.hxx"

namespace ltn::c {
	std::vector<std::uint8_t> assemble(
		const Instructions & instructions);
}