#pragma once
#include <vector>
#include <variant>
#include <iostream>
#include <memory>
#include <optional>
#include "stdxx/heaped.hxx"

namespace ltn::c::type {
	template<typename T>
	concept AType = std::same_as<typename T::is_type, std::true_type>;

	class Type {
		struct Concept {
			virtual ~Concept() = default;
			virtual std::unique_ptr<Concept> clone() const = 0;
		};


		template<typename T>
		struct Model : Concept {
			Model(T type) : object { std::move(type) } {}
			T object;
			virtual std::unique_ptr<Concept> clone() const override {
				return std::make_unique<Model<T>>(object);
			}
		};

	public:
		template<AType T>
		Type(T type)
			: object { std::make_unique<Model<T>>(std::move(type)) } {}

		Type(const Type & other) {
			this->object = other.object->clone();
		}

		Type & operator=(const Type & other) {
			this->object = other.object->clone();
			return *this;
		}

		Type(Type &&) = default;

		Type & operator=(Type &&) = default; 
	
		template<typename T>
		const T * as() const {
			if(auto t = dynamic_cast<const Model<T> *>(this->object.get())) {
				return &t->object;
			}
			else {
				return nullptr;
			}
		}
	private:
		std::unique_ptr<Concept> object;
	};



	struct Other {
		using is_type = std::true_type;
		std::string type_name;
	};



	struct Optional {
		using is_type = std::true_type;
		Type contains;
	};



	struct Any {
		using is_type = std::true_type;
		constexpr static auto type_name = "any";
	};



	struct Error {
		using is_type = std::true_type;
		constexpr static auto type_name = "error";
	};



	struct Null {
		using is_type = std::true_type;
		constexpr static auto type_name = "null";
	};



	struct Bool {
		using is_type = std::true_type;
		constexpr static auto type_name = "bool";
	};



	struct Char {
		using is_type = std::true_type;
		constexpr static auto type_name = "char";
	};



	struct Int {
		using is_type = std::true_type;
		constexpr static auto type_name = "int";
	};



	struct Float {
		using is_type = std::true_type;
		constexpr static auto type_name = "float";
	};



	struct String {
		using is_type = std::true_type;
		constexpr static auto type_name = "string";
	};



	struct Array {
		using is_type = std::true_type;
		std::optional<Type> contains;
	};



	struct Tuple {
		using is_type = std::true_type;
		std::vector<Type> contained;
	};
	


	struct FxPtr {
		using is_type = std::true_type;
		Type return_type;
		std::vector<Type> parameter_types;
	};



	struct Queue {
		using is_type = std::true_type;
		Type contains;
	};



	struct Stack {
		using is_type = std::true_type;
		Type contains;
	};



	struct Map {
		using is_type = std::true_type;
		Type key;
		Type val;
	};



	struct Istream {
		using is_type = std::true_type;
		constexpr static auto type_name = "istream";
	};



	struct Ostream {
		using is_type = std::true_type;
		constexpr static auto type_name = "ostream";
	};



	struct Auto{};



	auto visit(const Type & type, const auto & fx) {
		if(auto t = type.as<Any>())      return fx(*t);
		if(auto t = type.as<Other>())    return fx(*t);
		if(auto t = type.as<Optional>()) return fx(*t);
		if(auto t = type.as<Error>())    return fx(*t);
		if(auto t = type.as<Null>())     return fx(*t);
		if(auto t = type.as<Bool>())     return fx(*t);
		if(auto t = type.as<Char>())     return fx(*t);
		if(auto t = type.as<Int>())      return fx(*t);
		if(auto t = type.as<Float>())    return fx(*t);
		if(auto t = type.as<String>())   return fx(*t);
		if(auto t = type.as<Array>())    return fx(*t);
		if(auto t = type.as<Tuple>())    return fx(*t);
		if(auto t = type.as<FxPtr>())    return fx(*t);
		if(auto t = type.as<Queue>())    return fx(*t);
		if(auto t = type.as<Stack>())    return fx(*t);
		if(auto t = type.as<Map>())      return fx(*t);
		if(auto t = type.as<Istream>())  return fx(*t);
		if(auto t = type.as<Ostream>())  return fx(*t);
		throw std::runtime_error{"Unknown type"};
	}



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
	std::strong_ordering operator<=>(const Tuple & l, const Tuple & r);
	std::strong_ordering operator<=>(const FxPtr & l, const FxPtr & r);
	std::strong_ordering operator<=>(const Queue & l, const Queue & r);
	std::strong_ordering operator<=>(const Stack & l, const Stack & r);
	std::strong_ordering operator<=>(const Map & l, const Map & r);
	std::strong_ordering operator<=>(const Istream & l, const Istream & r);
	std::strong_ordering operator<=>(const Ostream & l, const Ostream & r);

	inline bool operator==(const Type & l, const Type & r) {
		return (l <=> r) == 0;
	}
	

	std::ostream & operator<<(std::ostream & out, const Type & type);
}