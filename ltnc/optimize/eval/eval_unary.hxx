#pragma once
#include "ltnc/ast/Ast.hxx"
#include "to_node_type.hxx"
namespace ltn::c {



	struct Negation {
		template<sst::literal_type Litr>
		auto operator()(const Litr & litr) const {
			auto result = eval(litr);
			using Node = typename node<decltype(result)>::type;
			return stx::make_unique<Node>(result, litr.location);
		}

		auto eval(const sst::literal_type auto & litr) const {
			return -litr.value + std::int64_t(0);
		}
	};



	struct Truthyness {
		auto eval(sst::literal_type auto & litr) const {
			return static_cast<bool>(litr.value);
		}


		auto eval(sst::String &) const {
			return true;
		}

		auto eval(sst::Array &) const {
			return true;
		}
	};



	struct Notigation : Truthyness {
		auto eval(sst::literal_type auto & litr) const {
			return !Truthyness::eval(litr);
		}

		auto operator()(sst::literal_type auto & litr) const {
			return stx::make_unique<sst::Bool>(eval(litr), litr.location);
		}
	};


	
	struct NullTest {
		auto eval(sst::literal_type auto &) const {
			return true;
		}
	
		auto eval(sst::Null &) const {
			return false;
		}

		auto operator()(sst::literal_type auto & litr) const {
			return stx::make_unique<sst::Bool>(eval(litr), litr.location);
		}
	};
}