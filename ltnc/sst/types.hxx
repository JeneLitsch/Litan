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

	}

	using bind_ptr = std::unique_ptr<bind::Binding>;
	using expr_ptr = std::unique_ptr<expr::Expression>;
}