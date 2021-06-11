#pragma once
#include <set>
#include <string>
#include <optional>
#include <cstdint>
#include "LtncType.hxx"
namespace ltnc {
	class TypeTable {
	public:
		void registerType(const std::string & typeName);
		bool checkType(const Type & type) const;
		void guardType(const Type & type) const;
	private:
		std::set<std::string> types;
	};
}