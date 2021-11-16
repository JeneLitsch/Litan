#pragma once
#include <vector>
#include <string>
namespace ltn::c::type {
	struct Type {
		Type(
			const std::string & name,
			std::vector<Type> && contained) 
			:	name(name),
				contained(std::move(contained)) {}
			
			Type(const std::string & name)
			:	name(name) {}

			Type(const std::string_view & name)
			:	name(name) {}
		
		virtual ~Type() = default;
		std::string name;
		std::vector<Type> contained;
	};


	bool operator==(const Type & l, const Type & r);
	bool operator!=(const Type & l, const Type & r);
	std::ostream & operator<<(std::ostream & out, const Type & type);

	bool isVoid(const Type & type);
	bool isInt(const Type & type);
	bool isFloat(const Type & type);
	bool isBool(const Type & type);
}