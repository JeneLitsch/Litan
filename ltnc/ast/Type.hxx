#pragma once
#include "Node.hxx"

namespace ltn::c::ast {
	struct Type {
		virtual ~Type() = default;
	};

	struct TypeName : public Type {
		TypeName(const std::string & name) : name(name) {}
		virtual ~TypeName() = default;
		std::string name;
	};

	struct TypeContainer : public Type {
		TypeContainer(
			const std::string & name,
			std::unique_ptr<Type> && contained) 
			:	name(name),
				contained(std::move(contained)) {}
		virtual ~TypeContainer() = default;
		std::string name;
		std::unique_ptr<Type> contained;
	};
}