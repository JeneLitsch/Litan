#pragma once
#include <set>
#include <string>
#include <optional>
#include <cstdint>
#include "LtncType.hxx"
namespace ltnc {
	class TypeTable {
	public:
		void registerType(const Type & type);
		bool checkType(const std::string & typeName) const;
		void guardType(const std::string & typeName) const;
		const Type & getType(const std::string & typeName) const;
	private:
		std::set<Type> types;
	};
}