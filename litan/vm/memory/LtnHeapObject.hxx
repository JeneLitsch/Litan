#pragma once
#include <vector>
#include <cstdint>
#include <variant>
namespace ltn {
	struct HeapObject {
		enum class Type {
			ARRAY,
		};
		HeapObject(Type type) : type(type) {
			if(this->type == Type::ARRAY) {
				data = std::vector<std::uint64_t>();
			}
		}

		const Type type;
		std::variant<
			std::vector<std::uint64_t>
		> data;
	};
}
