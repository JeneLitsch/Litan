#pragma once
#include "ltnc/inst/inst.hxx"
#include "ltnc/link/LinkInfo.hxx"

namespace ltn::c {
	std::vector<std::uint8_t> assemble(
		const std::vector<inst::Inst> & instructions,
		const LinkInfo & link_info);
}