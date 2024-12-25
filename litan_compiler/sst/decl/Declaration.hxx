#pragma once
#include <map>
#include "litan_compiler/Namespace.hxx"
#include "litan_compiler/sst/Node.hxx"
#include "litan_compiler/sst/types.hxx"

namespace ltn::c::sst::decl {
	struct Global;
	struct Definition;

	struct Declaration : public Node {
		Declaration(
			const std::string & name,
			const Namespace & namespaze) 
			: name(name)
			, namespaze(namespaze) {}

		std::string name;
		Namespace namespaze;
	};
}