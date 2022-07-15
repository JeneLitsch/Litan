#pragma once
#include <vector>
#include <string>
#include <set>
#include <map>
#include "stdxx/args.hxx"

namespace ltn::args {
	auto & version(stx::option_description & desc) {
		return desc.add<stx::option_flag>(
			{"--version"},
			"Version",
			"If --version is set the current installed version is printed."
		);
	}

	auto & help(stx::option_description & desc) {
		return desc.add<stx::option_flag>(
			{"--help"},
			"Help",
			"Show explanation of options and usage."
		);
	}

	auto & main_args(stx::option_description & desc) {
		return desc.add<stx::option_string_list>(
			{"--args"},
			"Main arguments",
			"A list of strings passed to the main function of the Litan program."
		);
	}
}