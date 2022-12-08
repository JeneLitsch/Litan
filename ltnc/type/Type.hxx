#pragma once
#include <vector>
#include <variant>
#include <iostream>
#include <optional>
#include "stdxx/heaped.hxx"

namespace ltn::c::type {
	class Complete{};
	
	template<typename Flavor>
	class BasicType;

	struct Other {
		std::string type_name;
	};

	template<typename T>
	struct BasicOptional {
		constexpr static auto type_name = "optional";
		stx::heaped<T> contains;
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

	template<typename T>
	struct BasicArray {
		constexpr static auto type_name = "array";
		std::optional<stx::heaped<T>> contains;
	};
	



	template<typename T>
	struct BasicFxPtr {
		constexpr static auto type_name = "fx_ptr";
		std::optional<stx::heaped<T>> return_type;
		std::vector<T> parameter_types;
	};




	template<typename T>
	struct BasicQueue {
		constexpr static auto type_name = "queue";
		stx::heaped<T> contains;
	};




	template<typename T>
	struct BasicStack {
		constexpr static auto type_name = "stack";
		stx::heaped<T> contains;
	};




	template<typename T>
	struct BasicMap {
		constexpr static auto type_name = "map";
		std::optional<stx::heaped<T>> key;
		std::optional<stx::heaped<T>> val;
	};




	struct Auto{};


	template<typename Flavor>
	class BasicType {

		using Variant = std::variant<
			Any,
			Other,
			BasicOptional<BasicType>,
			Error,
			Null,
			Bool,
			Char,
			Int,
			Float,
			String,
			BasicArray<BasicType>,
			BasicFxPtr<BasicType>,
			BasicQueue<BasicType>,
			BasicStack<BasicType>,
			BasicMap<BasicType>
		>;

	public:
		BasicType(auto actual_type) : actual_type { actual_type } {} 
	
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

	using Type = BasicType<Complete>;

	using Optional = BasicOptional<Type>;
	using Array = BasicArray<Type>;
	using FxPtr = BasicFxPtr<Type>;
	using Queue = BasicQueue<Type>;
	using Stack = BasicStack<Type>;
	using Map = BasicMap<Type>;

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
	
	// inline bool operator==(const Any & l, const Any & r) { 				return (l <=> r) == 0;}
	// inline bool operator==(const Other & l, const Other & r) { 			return (l <=> r) == 0;}
	// inline bool operator==(const Optional & l, const Optional & r) { 	return (l <=> r) == 0;}
	// inline bool operator==(const Error & l, const Error & r) { 			return (l <=> r) == 0;}
	// inline bool operator==(const Null & l, const Null & r) { 			return (l <=> r) == 0;}
	// inline bool operator==(const Bool & l, const Bool & r) { 			return (l <=> r) == 0;}
	// inline bool operator==(const Char & l, const Char & r) { 			return (l <=> r) == 0;}
	// inline bool operator==(const Int & l, const Int & r) { 				return (l <=> r) == 0;}
	// inline bool operator==(const Float & l, const Float & r) { 			return (l <=> r) == 0;}
	// inline bool operator==(const String & l, const String & r) { 		return (l <=> r) == 0;}
	// inline bool operator==(const Array & l, const Array & r) { 			return (l <=> r) == 0;}
	// inline bool operator==(const FxPtr & l, const FxPtr & r) { 			return (l <=> r) == 0;}
	// inline bool operator==(const Queue & l, const Queue & r) { 			return (l <=> r) == 0;}
	// inline bool operator==(const Stack & l, const Stack & r) { 			return (l <=> r) == 0;}
	// inline bool operator==(const Map & l, const Map & r) { 				return (l <=> r) == 0;}


	std::ostream & operator<<(std::ostream & out, const Type & type);
}