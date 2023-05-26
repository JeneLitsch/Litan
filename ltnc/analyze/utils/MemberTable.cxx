#include "MemberTable.hxx"

namespace ltn::c {
	namespace {
		std::uint64_t resolve_member_id(auto & table, const std::string & str) {
			if(table.contains(str)) {
				return table.at(str);
			}
			const auto id = table.size() + 256;
			table.insert({str, id});
			return id;
		}



		std::uint64_t resolve_member_id(auto &, MemberCode code) {
			return static_cast<std::uint64_t>(code);
		}
	}

	std::uint64_t MemberTable::get_id(const std::variant<std::string, MemberCode> & name) {
		return std::visit([&] (auto & m) {
			return resolve_member_id(this->table, m);
		}, name);
	}
}