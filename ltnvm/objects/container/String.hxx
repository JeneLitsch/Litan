#pragma once
#include <string>
#include <optional>
#include <string_view>
#include "ltnvm/objects/Object.hxx"
#include "Container.hxx"

namespace ltn::vm {
	struct String : public Object {
		const static struct NonOwning {} non_owning;
		
		String(std::string str = {}) 
			: Object{}
			, storage {str}
			, str{*storage} {}
		
		String(const String & string)
			: Object { string } {
			if (string.storage) {
				storage = string.storage;
				str = storage.value();
			}
			else {
				str = string.str;
			}
		}

		String(std::string_view string, NonOwning)
			: Object {}
			, storage{std::nullopt}
			, str{string}
			{}

		virtual void stringify(VMCore & core, std::ostream & oss, bool nested) override;
		virtual Value get_member(std::uint64_t id) const override;

		// const std::string & get_underlying() const {
		// 	return *storage;
		// }

		bool empty() const {
			return std::empty(str);
		}

		char unsafe_back() const {
			return str.back();
		}

		char unsafe_front() const {
			return str.front();
		}

		char unsafe_at(std::int64_t i) const {
			return str[static_cast<std::uint64_t>(i)];
		}

		std::int64_t size() const {
			return std::ssize(str);
		}

		friend std::partial_ordering operator<=>(const String & l, const String & r) {
			return l.str <=> r.str;
		}

		std::string copy_to_std_string() const {
			if(storage) {
				return storage.value();
			}
			else {
				return std::string{str};
			}
		}

		std::optional<std::string> storage;
		std::string_view str;
	};


	inline String clone(const String & string) {
		return string;
	}
}