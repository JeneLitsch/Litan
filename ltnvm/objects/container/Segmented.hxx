#pragma once
#include <deque>
#include <string_view>
#include "ltnvm/Value.hxx"
#include "ltnvm/objects/Object.hxx"

namespace ltn::vm {
	struct Segmented : public Container<std::deque<Value>> {
	public:
		void pop_front() {
			++this->version;
			this->data.pop_front();
		}

	protected:
		Segmented(std_container data = {}) 
			: Container<std::deque<Value>> {data} {}
	};
}