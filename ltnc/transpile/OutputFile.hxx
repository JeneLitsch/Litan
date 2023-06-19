#pragma once
#include <filesystem>
#include <string>

namespace ltn::c {
	struct OutputFile {
		std::filesystem::path name;
		std::string content;
	};
}