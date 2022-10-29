#pragma once
#include <vector>
#include <variant>
#include <optional>
#include "stdxx/heaped.hxx"
#include "ltnc/type/to_string.hxx"
#include "ltnc/type/deduction.hxx"

namespace ltn::c::type {
	class Type;

	struct Optional {
		constexpr static auto type_name = "optional";
		stx::heaped<Type> contains;
	};

	struct Any {
		constexpr static auto type_name = "any";
	};

	struct Error {
		constexpr static auto type_name = "error";
	};

	struct Null {
		constexpr static auto type_name = "null";
	};

	struct Bool {
		constexpr static auto type_name = "bool";
	};

	struct Char {
		constexpr static auto type_name = "char";
	};

	struct Int {
		constexpr static auto type_name = "int";
	};

	struct Float {
		constexpr static auto type_name = "float";
	};

	struct String {
		constexpr static auto type_name = "string";
	};

	struct Array {
		constexpr static auto type_name = "array";
		std::optional<stx::heaped<Type>> contains;
	};

	struct Map {
		constexpr static auto type_name = "map";
		std::optional<stx::heaped<Type>> key;
		std::optional<stx::heaped<Type>> val;
	};
	
	struct FxPtr {
		constexpr static auto type_name = "fx_ptr";
		std::optional<stx::heaped<Type>> return_type;
		std::vector<Type> parameter_types;
	};


	struct Auto{};


	class Type {
		using Variant = std::variant<
			Optional,
			Any,
			Error,
			Null,
			Bool,
			Char,
			Int,
			Float,
			String,
			Array,
			Map,
			FxPtr
		>;
	public:
		Type(auto actual_type) : actual_type { actual_type } {} 
	
		template<typename T>
		const T * as() const {
			return std::get_if<T>(&actual_type);
		} 

		auto visit(const auto & visitor) {
			return std::visit(visitor, this->actual_type);
		}

		auto visit(const auto & visitor) const {
			return std::visit(visitor, this->actual_type);
		}

		friend bool operator==(const Type &, const Type &);
		// friend bool operator==(const Type &, const auto &);
		// friend bool operator==(const auto &, const Type &);
	
		const Variant & operator*() const {
			return this->actual_type;
		}
	private:
		
		Variant actual_type;
	};



	bool operator==(const Any &, const Any &);
	bool operator==(const Optional & l, const Optional & r);
	bool operator==(const Error &, const Error &);
	bool operator==(const Null &, const Null &);
	bool operator==(const Bool &, const Bool &);
	bool operator==(const Char &, const Char &);
	bool operator==(const Int &, const Int &);
	bool operator==(const Float &, const Float &);
	bool operator==(const String &, const String &);
	bool operator==(const Array & l, const Array & r);
	bool operator==(const Map & l, const Map & r);
	bool operator==(const FxPtr & l, const FxPtr & r);
	bool operator==(const Type & l, const Type & r);

	std::ostream & operator<<(std::ostream & out, const Type & type);
}