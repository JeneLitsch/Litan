#pragma once
#include "Node.hxx"
#include <vector>
namespace ltnc::ast {
	struct Expression : public Node {
		virtual ~Expression() = default;
	};

}