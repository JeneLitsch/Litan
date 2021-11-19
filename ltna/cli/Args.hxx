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
		const std::filesystem::path & getTarget() const;
		const std::filesystem::path & getSource() const;
	private:
		std::unordered_set<std::string> flags;
		std::filesystem::path source;
		std::filesystem::path target;
	};
}