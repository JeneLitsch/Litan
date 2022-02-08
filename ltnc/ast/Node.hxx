#pragma once
#include <memory>
#include "ltnc/SourceLocation.hxx"
namespace ltn::c::ast {
	struct Node {
		Node(const SourceLocation & location)
			:	location(location) {}
		virtual ~Node() = default;
		SourceLocation location;
	};
}