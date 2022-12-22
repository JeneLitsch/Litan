#pragma once
#include <filesystem>
#include <string>
#include <istream>
#include <memory>

namespace ltn::c {
	class FileSource {
	public:
		FileSource(std::filesystem::path path);
		std::unique_ptr<std::istream> make_istream() const;
		std::string get_name() const;
		std::string get_full_name() const;
	private:
		std::filesystem::path path;
	};
}