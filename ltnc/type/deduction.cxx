#include "ltnc/type/deduction.hxx"
#include "ltnc/type/Type.hxx"
#include <iostream>

namespace ltn::c::type {
	namespace {
		Type deduce_contained(const Array & l, const Array & r) {
			if(!l.contains && !r.contains) return Any{};
			
			if(!l.contains) return **r.contains;
			if(!r.contains) return **l.contains;

			if(**l.contains == **r.contains) return **l.contains;

			if((**l.contains).as<Array>() && (**r.contains).as<Array>()) {
				std::cout << type::to_string(l) << " + ";
				std::cout << type::to_string(r) << "\n";
				return Array{deduce_contained(
					*(**l.contains).as<Array>(),
					*(**r.contains).as<Array>())
				};
			}
			
			return Any{};
		}



		bool is_integral(const Type & x) {
			return x.as<Bool>() || x.as<Char>() || x.as<Int>();
		}



		bool is_numeric(const Type & x) {
			return is_integral(x) || x.as<Float>();
		}



		Array deduce_array_concat(const Array & l, const Array & r) {
			return Array{deduce_contained(l, r)};
		}



		Type deduce_arith_base(const Type & l, const Type & r) {
			if(l.as<Bool>()) {
				if(is_integral(r)) return Int{};
				if(r.as<Float>()) return Float{};
			} 
			if(l.as<Char>()) {
				if(is_integral(r)) return Int{};
				if(r.as<Float>()) return Float{};
			}
			if(l.as<Int>()) {
				if(is_integral(r)) return Int{};
				if(r.as<Float>()) return Float{};
			}
			if(l.as<Float>()) {
				if(is_numeric(r)) return Float{};
			}

			return Error{};
		}
	}



	Array deduce_array_append(const Array & array, const Type & elem) {
		return Array{deduce_contained(array, Array{elem})};
	}



	Type deduce_add(const Type & l, const Type & r) {
		if(l.as<Any>()) return Any{};
		if(r.as<Any>()) return Any{};
		
		const auto l_arr = l.as<Array>();
		const auto r_arr = r.as<Array>();
		if(l_arr && r_arr) return deduce_array_concat(*l_arr, *r_arr);

		const auto l_str = l.as<String>();
		const auto r_str = r.as<String>();
		if(l_str && r_str) return String{};

		return deduce_arith_base(l, r);
	}



	Type deduce_sub(const Type & l, const Type & r) {
		return deduce_arith_base(l, r);
	}



	Type deduce_mlt(const Type & l, const Type & r) {
		return deduce_arith_base(l, r);
	}
	
	
	
	Type deduce_div(const Type & l, const Type & r) {
		return deduce_arith_base(l, r);

	}



	Type deduce_mod(const Type & l, const Type & r) {
		return deduce_arith_base(l, r);
	}



	Type deduce_pow(const Type & l, const Type & r) {
		if(l.as<Any>()) return Any{};
		if(r.as<Any>()) return Any{};
		if(is_numeric(l) || is_numeric(r)) return Float{};
		return Error{};
	}



	Type deduce_neg(const Type & x) {
		if(x.as<Any>()) return Any{};
		if(x.as<Float>()) return Float{};
		if(is_integral(x)) return Int{};
		return Error{};
	}



	Type deduce_not(const Type & x) {
		return Bool{};
	}



	Type deduce_compare(const Type & l, const Type & r) {
		return Bool{};
	}



	Type deduce_three_way(const Type & l, const Type & r) {
		return Int{};
	}
}