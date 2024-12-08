#pragma once
#include <tuple>
#include "ltnvm/Heap.hxx"
#include "ltnvm/Value.hxx"
#include "ltnvm/utils/to_value.hxx"

namespace ltn::vm::ext {
	inline Value wrap_return(const Any & value, Heap &);
	
	inline Value wrap_return(bool value, Heap &);
		
	inline Value wrap_return(std::integral auto value, Heap &);
		
	inline Value wrap_return(std::floating_point auto value, Heap &);

	inline Value wrap_return(std::string value, Heap & heap);

	template <typename T>
	inline Value wrap_return(const std::optional<T> & value, Heap & heap);	
	
	template <typename T>
	inline Value wrap_return(const std::vector<T> & vector, Heap & heap);

	template <typename ...T>
	inline Value wrap_return(const std::tuple<T...> & tup, Heap & heap);



	inline Value wrap_return(const Any & value, Heap & heap) {
		return to_value(value, heap);
	}

	inline Value wrap_return(bool value, Heap &) {
		return value::boolean(value);
	}
		
	inline Value wrap_return(std::integral auto value, Heap &) {
		return value::integer(value);
	}
		
	inline Value wrap_return(std::floating_point auto value, Heap &) {
		return value::floating(value);
	}

	inline Value wrap_return(std::string value, Heap & heap) {
		auto ptr = heap.alloc(String{std::move(value)});
		return value::string(ptr);
	}

	template <typename T>
	inline Value wrap_return(const std::optional<T> & value, Heap & heap) {
		if(value) {
			return wrap_return(value.value(), heap);
		}
		else {
			return value::null;
		}
	}
	
	template <typename T>
	inline Value wrap_return(const std::vector<T> & vector, Heap & heap) {
		auto ptr = value::array(heap.make<Array>());
		auto & array = *value::as<Array>(ptr);
		for(const T & elem : vector) {
			array.push_back(wrap_return(elem, heap));
		} 
		return ptr;
	}

	namespace impl {
		template <typename ...T, std::size_t ... I>
		inline Value wrap_tuple(const std::tuple<T...> & tup, std::index_sequence<I...>, Heap & heap) {
			auto ptr = heap.make<Tuple>(std::vector{wrap_return(std::get<I>(tup), heap)...});
			return value::tuple(ptr);
		}
	}

	template <typename ...T>
	inline Value wrap_return(const std::tuple<T...> & tup, Heap & heap) {
		return impl::wrap_tuple(tup, std::make_index_sequence<sizeof...(T)>{}, heap);
	}

}