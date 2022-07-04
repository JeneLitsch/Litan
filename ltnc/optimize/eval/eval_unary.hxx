#pragma once
#include "ltnc/ast/Ast.hxx"
#include "to_node_type.hxx"
namespace ltn::c {



	struct Negation {
		template<ast::literal_type Litr>
		auto operator()(const Litr & litr) const {
			auto result = eval(litr);
			using Node = typename node<decltype(result)>::type;
			return std::make_unique<Node>(result, litr.location);
		}

		auto eval(const ast::literal_type auto & litr) const {
			return -litr.value + std::int64_t(0);
		}
	};



	struct Truthyness {
		auto eval(ast::literal_type auto & litr) const {
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
		auto eval(ast::literal_type auto & litr) const {
			return !Truthyness::eval(litr);
		}

		auto operator()(ast::literal_type auto & litr) const {
			return std::make_unique<ast::Bool>(eval(litr), litr.location);
		}
	};


	
	struct NullTest {
		auto eval(ast::literal_type auto &) const {
			return true;
		}
	
		auto eval(ast::Null &) const {
			return false;
		}

		auto operator()(ast::literal_type auto & litr) const {
			return std::make_unique<ast::Bool>(eval(litr), litr.location);
		}
	};
}