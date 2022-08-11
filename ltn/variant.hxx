#pragma once
#include <vector>
#include <variant>
#include <string>
#include <cstdint>
#include <ostream>
#include <optional>
#include "stdxx/float64_t.hxx"
#include "stdxx/array.hxx"

namespace ltn {

	class Variant {
		struct NullT {
			friend std::ostream & operator<<(std::ostream & stream, const NullT &) {
				stream << "null";
				return stream;
			}
		};
	public:
		Variant();
		Variant(bool v);
		Variant(char v);
		Variant(std::int64_t v);
		Variant(stx::float64_t v);
		Variant(const std::string v);
		Variant(const std::vector<Variant> & v);

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
		const std::vector<Variant> & as_array() const;
		
		friend std::ostream & operator<<(std::ostream & stream, const Variant & variant) {
			std::visit([&] (auto & value) { stream << value; }, variant.data);
			return stream;
		}

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
			std::vector<Variant>
		> data;
	};


	namespace internal {
		template<typename T>
		struct type {
			using get = T;
		};


		inline bool variant_cast_impl(type<bool>, const Variant & variant) {
			return variant.as_bool();
		}


		template<std::integral I>
		inline std::int64_t variant_cast_impl(type<I>, const Variant & variant) {
			return variant.as_int();
		}


		template<std::floating_point F>
		inline stx::float64_t variant_cast_impl(type<F>, const Variant & variant) {
			return variant.as_float();
		}

		
		inline std::string variant_cast_impl(type<std::string>, const Variant & variant) {
			return variant.as_string();
		}


		template<typename E>
		inline std::vector<E> variant_cast_impl(type<std::vector<E>>, const Variant & variant) {
			std::vector<E> vector;
			const auto & array = variant.as_array();
			for(const auto & elem : array) {
				vector.push_back(variant_cast_impl(type<E>{}, elem));
			} 
			return vector;
		}
	}


	template<typename T>
	inline std::optional<T> variant_cast(const Variant & variant) {
		internal::type<T> t;
		try {
			return internal::variant_cast_impl(t, variant);
		}
		catch(...) {
			return std::nullopt;
		}
	}
}