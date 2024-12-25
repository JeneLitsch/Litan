#pragma once
#include "litan_compiler/inst/inst.hxx"
#include "litan_compiler/link/LinkInfo.hxx"

namespace ltn::c {
	std::vector<std::uint8_t> assemble(
		const std::vector<inst::Inst> & instructions,
		const LinkInfo & link_info);
}