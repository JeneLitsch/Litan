#pragma once
#include <optional>
#include <vector>
#include <string>
#include <memory>
namespace ltnc {
	struct Var;
	struct Type {
		Type(const std::string & name) : name(name) {}
		
		Type() : name("voi") {}
		std::string name;
		std::vector<std::shared_ptr<Var>> members;
		unsigned fixedSize = 0;
	};

	inline bool operator==(const Type & typeL, const Type & typeR) {
		return typeL.name == typeR.name;
	}
	inline bool operator<(const Type & typeL, const Type & typeR) {
		return typeL.name < typeR.name;
	}
	inline bool operator>(const Type & typeL, const Type & typeR) {
		return typeL.name > typeR.name;
	}


	inline bool operator==(const Type & type, const std::string & name) {
		return type.name == name;
	}
	inline bool operator<(const Type & type, const std::string & name) {
		return type.name < name;
	}
	inline bool operator>(const Type & type, const std::string & name) {
		return type.name > name;
	}


	inline bool operator==(const std::string & name, const Type & type) {
		return type.name == name;
	}
	inline bool operator<(const std::string & name, const Type & type) {
		return type.name > name;
	}
	inline bool operator>(const std::string & name, const Type & type) {
		return type.name < name;
	}
}