#pragma once
#include <memory>

namespace ltn::c::ast {
	namespace bind {
		struct Binding;
	}

	namespace decl {
		struct Definition;
		struct Global;
		struct Function;
		struct Enumeration;
	}

	namespace expr {
		struct Expression;
		struct Type;
	}

	namespace stmt {
		struct Statement;
	}

	using defn_ptr = std::unique_ptr<decl::Definition>;
	using glob_ptr = std::unique_ptr<decl::Global>;
	using func_ptr = std::unique_ptr<decl::Function>;
	using enum_ptr = std::unique_ptr<decl::Enumeration>;

	using bind_ptr = std::unique_ptr<bind::Binding>;
	using expr_ptr = std::unique_ptr<expr::Expression>;
	using stmt_ptr = std::unique_ptr<stmt::Statement>;
	
	using type_ptr = std::unique_ptr<expr::Type>;
}