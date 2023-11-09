#pragma once
#include <memory>

namespace ltn::c::sst {
	namespace bind {
		struct Binding;
	}

	namespace decl {

	}

	namespace expr {
		struct Expression;
	}

	namespace stmt {
		struct Statement;
	}

	using bind_ptr = std::unique_ptr<bind::Binding>;
	using expr_ptr = std::unique_ptr<expr::Expression>;
	using stmt_ptr = std::unique_ptr<stmt::Statement>;
}