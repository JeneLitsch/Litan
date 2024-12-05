#pragma once
#include <vector>
#include <variant>
#include <string>
#include <cstdint>
#include <ostream>
#include <optional>
#include "stdxx/float64_t.hxx"
#include "stdxx/array.hxx"
#include "stdxx/io.hxx"

namespace ltn {

	class Any {
	public:
		struct NullT {};
		Any();
		Any(bool v);
		Any(char v);
		Any(std::int64_t v);
		Any(std::integral auto v) : Any{static_cast<std::int64_t>(v)} {}
		Any(stx::float64_t v);
		Any(const std::string v);
		Any(const std::vector<Any> & v);

		bool is_null() const;
		bool is_bool() const;
		bool is_char() const;
		bool is_int() const;
		bool is_float() const;
		bool is_string() const;
		bool is_array() const;

		const bool & as_bool() const;
		const char & as_char() const;
		const std::int64_t & as_int() const;
		const stx::float64_t & as_float() const;
		const std::string & as_string() const;
		const std::vector<Any> & as_array() const;
		
		friend std::ostream & operator<<(std::ostream & stream, const Any & any);

		static Any from_string(const std::string & str);

	private:
		template<typename T>
		bool is() const {
			return std::get_if<T>(&this->data);
		}

		template<typename T>
		const T & get() const {
			if(auto v = std::get_if<T>(&this->data)) {
				return *v;
			}
			throw std::bad_cast {};
		}

		std::variant<
			NullT,
			bool,
			char,
			std::int64_t,
			stx::float64_t,
			std::string,
			std::vector<Any>
		> data;
	};


	namespace internal {
		template<typename T>
		struct type {
			using get = T;
		};


		inline bool cast_impl(type<bool>, const Any & any) {
			return any.as_bool();
		}


		template<std::integral I>
		inline std::int64_t cast_impl(type<I>, const Any & any) {
			return any.as_int();
		}


		template<std::floating_point F>
		inline stx::float64_t cast_impl(type<F>, const Any & any) {
			return any.as_float();
		}

		
		inline std::string cast_impl(type<std::string>, const Any & any) {
			return any.as_string();
		}


		template<typename E>
		inline std::vector<E> cast_impl(type<std::vector<E>>, const Any & any) {
			std::vector<E> vector;
			const auto & array = any.as_array();
			for(const auto & elem : array) {
				vector.push_back(cast_impl(type<E>{}, elem));
			} 
			return vector;
		}
	}


	template<typename T>
	inline std::optional<T> cast(const Any & any) {
		internal::type<T> t;
		try {
			return internal::cast_impl(t, any);
		}
		catch(...) {
			return std::nullopt;
		}
	}
}