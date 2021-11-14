#pragma once
#include "Node.hxx"
#include <vector>
namespace ltn::c::ast {
	struct Expression : public Node {
		virtual ~Expression() = default;
	};

}