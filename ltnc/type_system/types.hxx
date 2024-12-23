#pragma once
#include <variant>
#include <memory>
#include "types/null.hxx"
#include "types/any.hxx"
#include "types/boolean.hxx"
#include "types/integer.hxx"
#include "types/floating.hxx"

namespace ltn::c::type {
	using TypeVariant = std::variant <
		Any, Null,
		Boolean, Integer, Floating>;



	class Type {
	public:
		template<typename T>
		Type(T && t) 
			: underlying { std::forward<T>(t) }
			{}
		
		template<typename T>	
		bool is() const {
			return std::holds_alternative<T>(underlying);
		}
	private:
		TypeVariant underlying;
	};



	using type_ptr = std::unique_ptr<Type>;
}