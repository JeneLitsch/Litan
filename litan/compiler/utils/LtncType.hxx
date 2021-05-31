#pragma once
#include <optional>
#include <memory>
#include <string>
namespace ltnc {
	struct Type {
		Type(const std::string & typeName) : typeName(typeName) {}
		
		Type() : typeName("voi") {}

		inline bool operator==(const std::string & typeName) const {
			return this->typeName == typeName;
		}

		inline bool operator==(Type other) const {
			return this->typeName == other.typeName;
		}
		std::string typeName;
	};

}