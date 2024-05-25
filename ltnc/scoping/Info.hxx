#pragma once
#include <cstdint>
#include "stdxx/reference.hxx"

namespace ltn::c {
	namespace ast::decl {
		struct Function;
	}
	namespace sst::decl {
		struct Global;
		struct Definition;
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

	struct GlobalVariableInfo {
		stx::reference<const sst::decl::Global> ast_node;
	};

	struct DefinitionInfo {
		stx::reference<const sst::decl::Definition> ast_node;
	};
}