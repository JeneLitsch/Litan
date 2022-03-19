#pragma once
#include <memory>
#include "ltn/float64_t.hxx"
#include "ltnc_core/SourceLocation.hxx"
namespace ltn::c::ast {
	struct Node {
		Node(const SourceLocation & location)
			:	location(location) {}
		virtual ~Node() = default;
		SourceLocation location;
	};
}