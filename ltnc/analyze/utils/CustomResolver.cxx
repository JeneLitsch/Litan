#include "CustomResolver.hxx"

namespace ltn::c {
	CustomResolver::CustomResolver(const std::vector<CustomLiteral> & literals) {
		for(const auto & lit : literals) {
			this->table.insert({lit.get_type(), lit});
		}
	}



	sst::expr_ptr CustomResolver::resolve(
		const std::string & type,
		const std::string & value) {

		if(this->table.contains(type)) {
			return this->table.at(type)(value);
		}
		else {
			throw std::runtime_error{""};
		}
	}
}