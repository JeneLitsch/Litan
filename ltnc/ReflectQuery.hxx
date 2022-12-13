#pragma once
#include <variant>
#include "Namespace.hxx"

namespace ltn::c {
	struct NamespaceQuery {
		Namespace namespaze;
	};
	struct FunctionQuery {
		Namespace namespaze;
		std::string name;
		std::size_t arity;
	};
	using ReflectQuery = std::variant<
		NamespaceQuery,
		FunctionQuery
	>;
}