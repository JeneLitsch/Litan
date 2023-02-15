#pragma once
#include "stdxx/memory.hxx"
#include "stdxx/float64_t.hxx"
#include "ltnc/SourceLocation.hxx"
#include "ltnc/type/Type.hxx"

namespace ltn::c::ast {
	class Node {
	public:
		Node(const SourceLocation & location)
			: location(location) {}
		virtual ~Node() = default;
		
		Node(Node &&) = default;
		Node & operator=(Node &&) = default;
		
		inline friend const SourceLocation & location(const Node & node);
		SourceLocation location;
	};


	inline const SourceLocation & location(const Node & node) {
		return node.location;
	}
}