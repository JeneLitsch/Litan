#pragma once
#include <filesystem>
#include <string>
#include <istream>
#include <memory>
#include <vector>
#include "Source.hxx"

namespace ltn::c {
	class FileSource {
	public:
		FileSource(std::filesystem::path path);
		std::unique_ptr<std::istream> make_istream() const;
		std::string get_name() const;
		std::string get_full_name() const;
		std::vector<Source> get_module_subsources() const { return {}; };
	private:
		std::filesystem::path path;
	};
}