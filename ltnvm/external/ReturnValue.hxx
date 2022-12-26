#pragma once
#include <vector>
#include "stdxx/float64_t.hxx"
#include "ltnvm/memory/Value.hxx"
#include "ltnvm/memory/Heap.hxx"
#include "ltnvm/type_check.hxx"

namespace ltn::vm::ext {
	class ReturnValue {
	public:
		ReturnValue(Heap & heap, Register & reg);

		void set(bool value) {
			this->returned_value = value::boolean(value);
		}
		
		void set(std::integral auto value) {
			this->returned_value = value::integer(value);
		}
		
		void set(std::floating_point auto value) {
			this->returned_value = value::floating(value);
		}

		void set(const std::string & value) {
			auto ptr = this->heap.alloc<String>({value});
			this->returned_value = value::string(ptr);
		}

		virtual ~ReturnValue();

	private:
		Heap & heap;
		Register & reg;
		Value returned_value;
	};
}