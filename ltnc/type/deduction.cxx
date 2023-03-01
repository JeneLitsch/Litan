#include "ltnc/type/deduction.hxx"
#include "ltnc/type/Type.hxx"
#include "ltnc/type/traits.hxx"
#include "stdxx/array.hxx"
#include <iostream>

namespace ltn::c::type {
	namespace {

		Type largest_common_type(const Type & l, const Type & r);



		Type largest_common_type(const Array & l, const Array & r) {
			if(!l.contains && !r.contains) return Array{};
			if(!l.contains) return Array{*r.contains};
			if(!r.contains) return Array{*l.contains};
			return Array{largest_common_type(*l.contains, *r.contains)};
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
				if(is_float(r)) return Float{};
			}
			if(is_float(l)) {
				if(is_numeric(r)) return Float{};
			}

			if(is_any(l) || is_any(r)) return Any{};

			return Error{};
		}
	}



	Array deduce_array_append(const Array & array, const Type & elem) {
		if(!array.contains) return Array{elem};
		return Array{ largest_common_type(*array.contains, elem) };
	}



	Array deduce_array_of(const std::vector<Type> & elem_types) {
		Array array{};
		for(const auto & elem_type : elem_types) {
			array = type::deduce_array_append(array, elem_type);
		}
		return array;
	}



	Tuple deduce_tuple_of(const std::vector<Type> & elem_types) {
		return Tuple {
			.contained = elem_types
		};
	}




	Type deduce_add(const Type & l, const Type & r) {
		if(is_any(l)) return Any{};
		if(is_any(r)) return Any{};
		
		const auto l_arr = l.as<Array>();
		const auto r_arr = r.as<Array>();
		if(l_arr && r_arr) return largest_common_type(*l_arr, *r_arr);

		const auto l_tpl = l.as<Tuple>();
		const auto r_tpl = r.as<Tuple>();
		if(l_tpl && r_tpl) {
			return Tuple { l_tpl->contained + r_tpl->contained };
		} 

		const auto l_str = l.as<String>();
		const auto r_str = r.as<String>();
		if(l_str && r_str) return String{};

		return deduce_arith_base(l, r);
	}



	Type deduce_sub(const Type & l, const Type & r) {
		return deduce_arith_base(l, r);
	}



	Type deduce_mlt(const Type & l, const Type & r) {
		if(is_integral(l) && is_string(r)) return r;
		if(is_string(l) && is_integral(r)) return l;
		if(is_integral(l) && is_array(r)) return r;
		if(is_array(l) && is_integral(r)) return l;
		return deduce_arith_base(l, r);
	}
	
	
	
	Type deduce_div(const Type & l, const Type & r) {
		return deduce_arith_base(l, r);
	}



	Type deduce_mod(const Type & l, const Type & r) {
		return deduce_arith_base(l, r);
	}



	Type deduce_pow(const Type & l, const Type & r) {
		return deduce_arith_base(l, r);
	}



	Type deduce_bitwise(const Type & l, const Type & r) {
		if(is_any(l)) return Int{};
		if(is_any(r)) return Int{};
		if(is_integral(l) && is_integral(r)) return Int{};
		return Error{};
	}



	Type deduce_compare(const Type &, const Type &) {
		return Bool{};
	}
	


	namespace {
		Type deduce_index_map(const Map & map, const Type & key) {
			if(is_any(map.key) || map.key == key) {
				return Optional{map.val};
			}
			return Error{};
		}



		Type deduce_index_array(const Array & array, const Type & key) {
			if(is_numeric(key) || is_any(key)) {
				if(array.contains) return *array.contains;
				else return Any{};
			}
			return Error{};
		}


		
		Type deduce_index_tuple(const Tuple & tuple, const Type & key, std::optional<std::uint64_t> index) {
			if(is_numeric(key) || is_any(key)) {
				if(!index) return Any{};
				if(*index >= std::size(tuple.contained)) return Error{};
				return tuple.contained[*index];
			}
			return Error{};
		}



		Type deduce_index_string(const String &, const Type & key) {
			if(is_numeric(key) || is_any(key)) {
				return Char{};
			}
			return Error{};
		}
	}



	Type deduce_three_way(const Type &, const Type &) {
		return Int{};
	}
	


	Type deduce_index(const Type & container, const Type & key, std::optional<std::uint64_t> index) {
		if(is_any(container)) return Any{};		
		if(auto map = container.as<Map>()) return deduce_index_map(*map, key);
		if(auto array = container.as<Array>()) return deduce_index_array(*array, key);
		if(auto tuple = container.as<Tuple>()) return deduce_index_tuple(*tuple, key, index);
		if(auto string = container.as<String>()) return deduce_index_string(*string, key);
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
			return deduce_nullco(l.as<Optional>()->contains, r);
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



	Type deduce_not(const Type &) {
		return Bool{};
	}

	
	
	Type deduce_bitnot(const Type & x) {
		if(x.as<Any>()) return Int{};
		if(is_integral(x)) return Int{};
		return Error{};
	}
	
	
	
	Type deduce_nulltest(const Type &) {
		return Bool{};
	}



	Type deduce_deref(const Type & x) {
		if(is_optional(x)) return x.as<Optional>()->contains;
		return x; 
	}



	Type deduce_invokation(const Type & fx_ptr) {
		if(auto fx = fx_ptr.as<FxPtr>()) return fx->return_type;
		if(fx_ptr.as<Any>()) return Any{};
		return Error{};
	}


	
	Type deduce_cast_static(const Type & cast_to) {
		return cast_to;
	}



	Type deduce_cast_dynamic(const Type & cast_to) {
		return type::Optional{
			.contains = cast_to
		};
	}



	Type deduce_cast_force(const Type & cast_to) {
		return cast_to;
	}



	Type deduce_copy_static(const Type & cast_to) {
		return cast_to;
	}



	Type deduce_copy_dynamic(const Type & cast_to) {
		return type::Optional{
			.contains = cast_to
		};
	}



	Type deduce_copy_force(const Type & cast_to) {
		return cast_to;
	}
}