#pragma once
#include <string>
#include <cstdint>
#include <unordered_map>
#include "ltnc/ast/Namespace.hxx"
namespace ltn::c::compile {
	// Tracks, stores and resolves local variables  
	class Scope {
	public:
		Scope(const ast::Namespace & nameSpace);
		Scope(const Scope * parent);
		std::uint64_t resolve(const std::string & name, std::size_t line) const;
		std::uint64_t insert(const std::string & name, std::size_t line);
		const ast::Namespace & getNamespace() const;
	private:
		std::uint64_t recSize() const;
		std::unordered_map<std::string, std::uint64_t> vars;
		const Scope * parent;
		const ast::Namespace & nameSpace;
	};
}