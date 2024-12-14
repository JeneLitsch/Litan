#pragma once
#include <string>
#include <string_view>
#include "ltnvm/objects/Object.hxx"
#include "Container.hxx"

namespace ltn::vm {
	struct String : public Container<std::string> {
		virtual void stringify(VMCore & core, std::ostream & oss, bool nested) override;
		virtual Value get_member(std::uint64_t id) const override;

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