#pragma once
#include "stdxx/memory.hxx"
#include "stdxx/float64_t.hxx"
#include "litan_compiler/SourceLocation.hxx"

namespace ltn::c::ast {
	class Node {
	public:
		Node(const SourceLocation & location)
			: location(location) {}
		virtual ~Node() = default;
		
		Node(const Node &) = default;
		Node(Node &&) = default;
		Node & operator=(const Node &) = default;
		Node & operator=(Node &&) = default;
		
		inline friend const SourceLocation & location(const Node & node);
	private:
		SourceLocation location;
	};


	inline const SourceLocation & location(const Node & node) {
		return node.location;
	}
}