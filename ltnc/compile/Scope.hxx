#pragma once
#include <string>
#include <cstdint>
#include <unordered_map>
#include "ltnc/ast/Namespace.hxx"
#include "Variable.hxx"
namespace ltn::c::compile {


	class Scope {
	public:
		Scope(const ast::Namespace & nameSpace);
		Scope(const Scope * parent);
		Variable resolve(const std::string & name, std::size_t line) const;
		Variable insert(const std::string & name, Variable::Qualifier qualifier, std::size_t line);
		Variable insert(const std::string & name, std::size_t line);
		const ast::Namespace & getNamespace() const;
	private:
		std::uint64_t recSize() const;
		std::unordered_map<std::string, Variable> vars;
		const Scope * parent;
		const ast::Namespace & nameSpace;
	};
}