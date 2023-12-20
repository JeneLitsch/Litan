#pragma once
#include <filesystem>
#include <vector>
#include "ltnc/source/Source.hxx"

namespace ltn::c {
	std::vector<ltn::c::Source> read_sources(
		const std::vector<std::filesystem::path> & filepaths);

	std::vector<ltn::c::Source> read_sources(
		const std::vector<std::string> & filepaths);
	
	void inject_stdlib(std::vector<ltn::c::Source> & sources);
}