#include "MemberTable.hxx"

namespace ltn::c::compile {
	std::uint64_t MemberTable::getId(const std::string & str) {
		if(this->table.contains(str)) {
			return this->table.at(str);
		}
		const auto id = this->table.size();
		this->table.insert({str, id});
		return id;
	}
}