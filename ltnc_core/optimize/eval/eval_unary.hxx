#pragma once
#include "ltnc_core/ast/Ast.hxx"
#include "../utils/concepts.hxx"
namespace ltn::c::optimize {


	template<literal_type T>
	struct promoted_t {
		using Type = T;
	};
	template<>
	struct promoted_t<ast::Bool> {
		using Type = ast::Integer;
	};
	template<>
	struct promoted_t<ast::Char> {
		using Type = ast::Integer;
	};
	template<literal_type T>
	using promoted = typename promoted_t<T>::Type;



	struct Negation {
		template<literal_type Litr>
		auto operator()(Litr & litr) const {
			using T = promoted<Litr>;
			return std::make_unique<T>(eval(litr), litr.location);
		}

		auto eval(literal_type auto & litr) const {
			return -litr.value;
		}
	};



	struct Truthyness {
		auto eval(literal_type auto & litr) const {
			return static_cast<bool>(litr.value);
		}


		auto eval(ast::String &) const {
			return true;
		}

		auto eval(ast::Array &) const {
			return true;
		}
	};



	struct Notigation : Truthyness {
		auto eval(literal_type auto & litr) const {
			return !Truthyness::eval(litr);
		}

		auto operator()(literal_type auto & litr) const {
			return std::make_unique<ast::Bool>(eval(litr), litr.location);
		}
	};


	
	struct NullTest {
		auto eval(literal_type auto &) const {
			return true;
		}
	
		auto eval(ast::Null &) const {
			return false;
		}

		auto operator()(literal_type auto & litr) const {
			return std::make_unique<ast::Bool>(eval(litr), litr.location);
		}
	};
}