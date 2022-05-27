#pragma once
#include <memory>
#include "stdxx/float64_t.hxx"
#include "ltnc_core/SourceLocation.hxx"
namespace ltn::c::ast {
	struct Node {
		Node(const SourceLocation & location)
		:	location(location) {}
		virtual ~Node() = default;
		SourceLocation location;
		
		Node(const Node &) = delete;
		Node(Node &&) = delete;
		Node & operator=(const Node &) = delete;
		Node & operator=(Node &&) = delete;
	};
}