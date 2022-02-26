#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <span>
#include <filesystem>
#include <unordered_set>
namespace ltn::c {
	class Args {
	public:
		Args(const char ** argv, std::size_t argc);
		const std::span<const std::filesystem::path> get_sources() const;
		const std::filesystem::path & get_target() const;
		const std::filesystem::path & get_stdlib() const;
		bool is_set(const std::string & flag) const;
	private:
		std::unordered_set<std::string> flags;
		std::vector<std::filesystem::path> files;
	};
}