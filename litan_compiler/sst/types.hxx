#pragma once
#include <memory>

namespace ltn::c::sst {
	namespace bind {
		struct Binding;
	}

	namespace decl {
		struct Declaration;
		struct Definition;
		struct Function;
		struct Global;
		struct Static;
	}

	namespace expr {
		struct Expression;
	}

	namespace stmt {
		struct Statement;
	}

	using defn_ptr = std::unique_ptr<decl::Definition>;
	using glob_ptr = std::unique_ptr<decl::Global>;
	using func_ptr = std::unique_ptr<decl::Function>;

	using bind_ptr = std::unique_ptr<bind::Binding>;
	using expr_ptr = std::unique_ptr<expr::Expression>;
	using stmt_ptr = std::unique_ptr<stmt::Statement>;
}