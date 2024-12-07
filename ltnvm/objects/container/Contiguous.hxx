#pragma once
#include <vector>
#include <string_view>
#include "ltnvm/Value.hxx"
#include "ltnvm/objects/Object.hxx"
#include "Container.hxx"

namespace ltn::vm {
	struct Contiguous : public Container<std::vector<Value>> {
	public:
		void unsafe_insert(iterator iter, const Value & value) {
			++this->version;
			this->data.insert(iter, value);
		}

	protected:
		Contiguous(std_container data = {}) 
			: Container<std::vector<Value>> {data} {}
	};
}