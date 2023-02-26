#pragma once
#include <filesystem>
#include <vector>
#include "ltnc/source/Source.hxx"
#include "ltnc/Reporter.hxx"

namespace ltn::c {
	std::vector<ltn::c::Source> read_sources(
		const std::vector<std::filesystem::path> & filepaths,
		ltn::c::Reporter & reporter);

	std::vector<ltn::c::Source> read_sources(
		const std::vector<std::string> & filepaths,
		ltn::c::Reporter & reporter);
}