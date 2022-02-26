#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <span>
#include <filesystem>
#include <unordered_set>
namespace ltn::a {
	class Args {
	public:
		Args(const char ** argv, std::size_t argc);
		const std::filesystem::path & get_target() const;
		const std::filesystem::path & get_source() const;
	private:
		std::unordered_set<std::string> flags;
		std::filesystem::path source;
		std::filesystem::path target;
	};
}