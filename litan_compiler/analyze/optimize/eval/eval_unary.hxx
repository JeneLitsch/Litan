#pragma once
#include "litan_compiler/ast/AST.hxx"
#include "to_node_type.hxx"
#include "litan_compiler/sst/expr/Literal.hxx"

namespace ltn::c {
	struct Negation {
		template<sst::expr::literal_type Litr>
		auto operator()(const Litr & litr) const {
			auto result = eval(litr);
			using Node = typename node<decltype(result)>::type;
			return stx::make_unique<Node>(result);
		}

		auto eval(const sst::expr::literal_type auto & litr) const {
			return -litr.value + std::int64_t(0);
		}
	};



	struct Truthyness {
		auto eval(sst::expr::literal_type auto & litr) const {
			return static_cast<bool>(litr.value);
		}


		auto eval(sst::expr::String &) const {
			return true;
		}

		auto eval(sst::expr::Array &) const {
			return true;
		}
	};



	struct Notigation : Truthyness {
		auto eval(sst::expr::literal_type auto & litr) const {
			return !Truthyness::eval(litr);
		}

		auto operator()(sst::expr::literal_type auto & litr) const {
			return sst::expr::boolean(eval(litr));
		}
	};


	
	struct NullTest {
		auto eval(sst::expr::literal_type auto &) const {
			return true;
		}
	
		auto eval(sst::expr::Null &) const {
			return false;
		}

		auto operator()(sst::expr::literal_type auto & litr) const {
			return sst::expr::boolean(eval(litr));
		}
	};
}