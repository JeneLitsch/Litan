#pragma once
#include <vector>
#include <cstdint>
#include <variant>
namespace ltn {
	struct HeapObject {
		enum class Type {
			ARRAY,
			STRING,
		};
		HeapObject(Type type) : type(type) {
			if(this->type == Type::ARRAY) {
				data = std::vector<std::uint64_t>();
			}
			if(this->type == Type::STRING) {
				data = std::string();
			}
			this->refCount = 1;
		}

		const Type type;
		unsigned refCount;
		std::variant<
			std::vector<std::uint64_t>,
			std::string
		> data;
	};
}
