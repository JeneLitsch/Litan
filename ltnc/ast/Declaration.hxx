#pragma once
#include "Node.hxx"
#include <map>

namespace ltn::c::ast {
	struct Declaration : public Node {
		Declaration(const SourceLocation & location) : Node(location) {}
		virtual ~Declaration() = default;
	};



	struct Enum : public Declaration {
		Enum(const SourceLocation & location) : Declaration(location) {}
		virtual ~Enum() = default;
		std::string name;
		std::map<std::string, std::int64_t> values;
	};
}