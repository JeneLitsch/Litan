#pragma once
#include "stdxx/memory.hxx"
#include "stdxx/float64_t.hxx"
#include "ltnc/SourceLocation.hxx"
namespace ltn::c::sst {
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