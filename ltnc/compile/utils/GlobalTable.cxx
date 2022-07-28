#include "GlobalTable.hxx"

namespace ltn::c {
	std::uint64_t GlobalTable::get_id(const std::string & str) {
		if(this->table.contains(str)) {
			return this->table.at(str);
		}
		const auto id = this->table.size();
		this->table.insert({str, id});
		return id;
	}
}