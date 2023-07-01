#pragma once
#include <memory>

namespace ltn::vm {
	struct Object {
		Object() {}
		virtual ~Object() = default;

		Object(const Object & other) {
			this->marked = other.marked;
			this->next_object = nullptr;
		}


		Object(Object && other) {
			this->marked = other.marked;
			this->next_object = nullptr;
		}


		bool marked = false;
		std::unique_ptr<Object> next_object;
	};
}