#include "MemberTable.hxx"
#include <optional>
#include <map>

namespace ltn::c {
	MemberTable::MemberTable() {
		// Inject reserved member codes
		this->table.insert(
			std::begin(ltn::reserved_member_name_to_code),
			std::end(ltn::reserved_member_name_to_code)
		);
	}



	std::uint64_t MemberTable::get_id(const std::string & name) {
		
		if(table.contains(name)) {
			return table.at(name);
		}
		const auto id = next_id++;
		table.insert({name, id});
		return id;
	}
}