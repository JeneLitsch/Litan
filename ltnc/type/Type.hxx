#pragma once
#include <vector>
#include <variant>
#include <optional>
#include "stdxx/heaped.hxx"
#include "ltnc/type/to_string.hxx"
#include "ltnc/type/deduction.hxx"

namespace ltn::c::type {
	class Type;

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
	


	class Type {
		using Variant = std::variant<
			Any,
			Error,
			Null,
			Bool,
			Char,
			Int,
			Float,
			String,
			Array
		>;
	public:
		Type(auto actual_type) : actual_type { actual_type } {} 
	
		template<typename T>
		const T * is() const {
			return std::get_if<const T *>(&actual_type);
		} 

		friend bool operator==(const Type &, const Type &);
	
		const Variant & operator*() const {
			return this->actual_type;
		}
	private:
		
		Variant actual_type;
	};



	inline bool operator==(const Any &, const Any &) {
		return true;
	}

	inline bool operator==(const Error &, const Error &) {
		return true;
	}

	inline bool operator==(const Null &, const Null &) {
		return true;
	}

	inline bool operator==(const Bool &, const Bool &) {
		return true;
	}

	inline bool operator==(const Char &, const Char &) {
		return true;
	}

	inline bool operator==(const Int &, const Int &) {
		return true;
	}

	inline bool operator==(const Float &, const Float &) {
		return true;
	}
	
	inline bool operator==(const String &, const String &) {
		return true;
	}

	inline bool operator==(const Array & l, const Array & r) {
		if(!l.contains && !r.contains) return true;
		if(l.contains && r.contains) return **l.contains == **r.contains;
		return false;
	}



	inline bool operator==(const Type & l, const Type & r) {
		return l.actual_type == r.actual_type;
	}
}