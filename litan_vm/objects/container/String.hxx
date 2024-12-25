#pragma once
#include <string>
#include <optional>
#include <string_view>
#include "litan_vm/objects/Object.hxx"
#include "Container.hxx"

namespace ltn::vm {
	struct String : public Object {
		enum class Encoding { ASCII, UTF8 };
		const static struct NonOwning {} non_owning;
		
		String(std::string str = {}, Encoding encoding = Encoding::UTF8); 
		String(const String & string);
		String(NonOwning, std::string_view string, Encoding encoding = Encoding::UTF8);

		virtual void stringify(VMCore & core, std::ostream & oss, bool nested) override;
		virtual Value get_member(std::uint64_t id) const override;

		bool empty() const;
		std::uint32_t unsafe_back() const;
		std::uint32_t back() const;
		std::uint32_t unsafe_front() const;
		std::uint32_t front() const;

		std::uint32_t at(std::int64_t i) const;

		std::int64_t size() const;
		std::string copy_to_std_string() const;

		friend std::partial_ordering operator<=>(const String & l, const String & r);

		operator std::string_view() const {
			return str;
		}

	private:
		std::optional<std::string> storage;
		std::string_view str;
		Encoding encoding;
		std::uint64_t character_count;
	};


	inline String clone(const String & string) {
		return string;
	}
}