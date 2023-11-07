#pragma once
#include <map>
#include "ltnc/Namespace.hxx"
#include "ltnc/sst/Node.hxx"

namespace ltn::c::sst {
	struct Expression;
	struct Integer;
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