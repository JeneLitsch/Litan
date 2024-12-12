#pragma once
#include <string>
#include <string_view>
#include "ltnvm/objects/Object.hxx"
#include "Container.hxx"

namespace ltn::vm {
	struct String : public Container<std::string> {
		virtual void stringify(VMCore &, std::ostream & oss, bool) override {
			oss << this->data;
		}

		void insert(iterator iter, auto begin, auto end) {
			++this->version;
			this->data.insert(iter, begin, end);
		}

		void append(const std::string & other) {
			++this->version;
			this->data.append(other);
		}

		String(std_container str = {}) 
			: Container<std::string> {str} {}
	};


	inline String clone(const String & string) {
		return string;
	}
}