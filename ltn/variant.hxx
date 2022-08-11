#pragma once
#include <vector>
#include <variant>
#include <string>
#include <cstdint>
#include "stdxx/float64_t.hxx"

namespace ltn {

	class Variant {
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

	private:
		template<typename T>
		bool is() const {
			return std::get_if<T>(&this->data);
		}

		template<typename T>
		const T * get() const {
			return std::get_if<T>(&this->data);
		}

		std::variant<
			std::monostate,
			bool,
			char,
			std::int64_t,
			stx::float64_t,
			std::string,
			std::vector<Variant>
		> data;
	};

	// template<typename T>
	// T variant_cast(const Variant & variant) {

	// }
}