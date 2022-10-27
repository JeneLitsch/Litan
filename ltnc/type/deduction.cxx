#include "ltnc/type/deduction.hxx"
#include "ltnc/type/Type.hxx"
#include "ltnc/type/check.hxx"
#include <iostream>

namespace ltn::c::type {
	namespace {

		Type largest_common_type(const Type & l, const Type & r);



		Type largest_common_type(const Array & l, const Array & r) {
			if(!l.contains && !r.contains) return Array{};
			if(!l.contains) return Array{**r.contains};
			if(!r.contains) return Array{**l.contains};
			return Array{largest_common_type(**l.contains, **r.contains)};
		}



		Type largest_common_type(const Type & l, const Type & r) {
			if(l == r) return l;
			auto l_arr = l.as<Array>(); 
			auto r_arr = r.as<Array>(); 
			if(l_arr && r_arr) return largest_common_type(*l_arr, *r_arr);
			return Any{};
		}



		Type deduce_arith_base(const Type & l, const Type & r) {
			if(is_integral(l)) {
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
		if(!array.contains) return Array{elem};
		return Array{ largest_common_type(**array.contains, elem) };
	}



	Type deduce_add(const Type & l, const Type & r) {
		if(l.as<Any>()) return Any{};
		if(r.as<Any>()) return Any{};
		
		const auto l_arr = l.as<Array>();
		const auto r_arr = r.as<Array>();
		if(l_arr && r_arr) return largest_common_type(*l_arr, *r_arr);

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
		if(is_numeric(l) && is_numeric(r)) return Float{};
		return Error{};
	}



	Type deduce_bitwise(const Type & l, const Type & r) {
		if(is_any(l)) return Int{};
		if(is_any(r)) return Int{};
		if(is_int(l) && is_int(r)) return Int{};
		return Error{};
	}






	Type deduce_compare(const Type & l, const Type & r) {
		return Bool{};
	}
	


	namespace {
		Type deduce_index_map(const Map & map, const Type & key) {
			if(!map.key || (**map.key).as<Any>() || **map.key == key) {
				if(map.val) return **map.val;
				return Any{};
			}
			return Error{};
		}



		Type deduce_index_array(const Array & array, const Type & key) {
			if(key.as<Int>() || key.as<Any>()) {
				if(array.contains) return **array.contains;
				else return Any{};
			}
			return Error{};
		}
	}



	Type deduce_three_way(const Type & l, const Type & r) {
		return Int{};
	}
	


	Type deduce_index(const Type & container, const Type & key) {
		if(container.as<Any>()) return Any{};		
		if(auto map = container.as<Map>()) return deduce_index_map(*map, key);
		if(auto array = container.as<Array>()) return deduce_index_array(*array, key);
		return Error{};
	}



	Type deduce_logic(const Type &, const Type &) {
		return Bool{};
	}



	Type deduce_elvis(const Type & l, const Type & r) {
		return largest_common_type(l, r);
	}



	Type deduce_nullco(const Type & l, const Type & r) {
		if(is_optional(l)) {
			return deduce_nullco(*l.as<Optional>()->contains, r);
		}
		else return largest_common_type(l, r);
	}



	Type deduce_ternary(const Type &, const Type & l, const Type & r) {
		return largest_common_type(l, r);
	}



	Type deduce_choose(const Type & current, const Type & next) {
		return largest_common_type(current, next);
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

	
	
	Type deduce_bitnot(const Type & x) {
		if(x.as<Any>()) return Int{};
		if(is_integral(x)) return Int{};
		return Error{};
	}
	
	
	
	Type deduce_nulltest(const Type & x) {
		return Bool{};
	}



	Type deduce_invokation(const Type & fx_ptr) {
		if(auto fx = fx_ptr.as<FxPtr>()) return **fx->return_type;
		if(fx_ptr.as<Any>()) return Any{};
		return Error{};
	}



	Type deduce_cast_static(const Type & cast_to) {
		return cast_to;
	}



	Type deduce_cast_dynamic(const Type & cast_to) {
		return type::Optional{cast_to};
	}
}