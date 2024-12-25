#pragma once
#include "stdxx/memory.hxx"
#include "stdxx/float64_t.hxx"
namespace ltn::c::sst {
	struct Node {
		Node() {}
		virtual ~Node() = default;
		
		Node(const Node &) = delete;
		Node(Node &&) = delete;
		Node & operator=(const Node &) = delete;
		Node & operator=(Node &&) = delete;
	};
}