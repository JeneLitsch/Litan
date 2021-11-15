#pragma once
#include "Node.hxx"

namespace ltn::c::ast {
	struct Declaration : public Node {
		virtual ~Declaration() = default;
	};
}