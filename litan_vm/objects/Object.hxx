#pragma once
#include <memory>
#include "litan_vm/Value.hxx"

namespace ltn::vm {
	struct VMCore;
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

		virtual Value get_member(std::uint64_t) const {
			return value::null;
		}

		virtual void stringify(VMCore &, std::ostream & oss, bool nested);
	};
}