#pragma once
#include <vector>
#include <variant>
#include <iostream>
#include <optional>
#include "stdxx/heaped.hxx"

namespace ltn::c::type {
	class Complete{};
	
	class Type;



	struct Other {
		std::string type_name;
	};



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
	


	struct FxPtr {
		constexpr static auto type_name = "fx_ptr";
		std::optional<stx::heaped<Type>> return_type;
		std::vector<Type> parameter_types;
	};



	struct Queue {
		constexpr static auto type_name = "queue";
		stx::heaped<Type> contains;
	};



	struct Stack {
		constexpr static auto type_name = "stack";
		stx::heaped<Type> contains;
	};



	struct Map {
		constexpr static auto type_name = "map";
		std::optional<stx::heaped<Type>> key;
		std::optional<stx::heaped<Type>> val;
	};



	struct Auto{};



	class Type {
		using Variant = std::variant<
			Any,
			Other,
			Optional,
			Error,
			Null,
			Bool,
			Char,
			Int,
			Float,
			String,
			Array,
			FxPtr,
			Queue,
			Stack,
			Map
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

		const Variant & operator*() const {
			return this->actual_type;
		}
	private:
		
		Variant actual_type;
	};

	struct IncompleteType {
		Type type;
	};

	std::strong_ordering operator<=>(const Type & l, const Type & r);
	std::strong_ordering operator<=>(const Any &, const Any &);
	std::strong_ordering operator<=>(const Other &, const Other &);
	std::strong_ordering operator<=>(const Optional & l, const Optional & r);
	std::strong_ordering operator<=>(const Error &, const Error &);
	std::strong_ordering operator<=>(const Null &, const Null &);
	std::strong_ordering operator<=>(const Bool &, const Bool &);
	std::strong_ordering operator<=>(const Char &, const Char &);
	std::strong_ordering operator<=>(const Int &, const Int &);
	std::strong_ordering operator<=>(const Float &, const Float &);
	std::strong_ordering operator<=>(const String &, const String &);
	std::strong_ordering operator<=>(const Array & l, const Array & r);
	std::strong_ordering operator<=>(const FxPtr & l, const FxPtr & r);
	std::strong_ordering operator<=>(const Queue & l, const Queue & r);
	std::strong_ordering operator<=>(const Stack & l, const Stack & r);
	std::strong_ordering operator<=>(const Map & l, const Map & r);

	inline bool operator==(const Type & l, const Type & r) {
		return (l <=> r) == 0;
	}
	

	std::ostream & operator<<(std::ostream & out, const Type & type);
}