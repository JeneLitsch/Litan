#pragma once
#include <string>
#include <cstdint>
#include <unordered_map>
namespace ltn::c::compile {
	// Tracks, stores and resolves local variables  
	class Scope {
	public:
		Scope(const Scope * parent = nullptr);
		std::uint64_t resolve(const std::string & name, std::size_t line) const;
		std::uint64_t insert(const std::string & name, std::size_t line);
	private:
		std::uint64_t recSize() const;
		std::unordered_map<std::string, std::uint64_t> vars;
		const Scope * parent;
	};
}