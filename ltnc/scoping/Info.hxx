#pragma once
#include <cstdint>
#include "stdxx/reference.hxx"

namespace ltn::c {
	namespace ast::decl {
		struct Function;
	}
	// Tracks, stores and resolves local variables  
	struct LocalVariableInfo {
		std::uint64_t address;
	};

	struct MemberInfo {
		std::uint64_t id;
	};

	struct FunctionInfo {
		stx::reference<const ast::decl::Function> ast_node;
	};
}