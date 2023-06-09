#include "CustomResolver.hxx"

namespace ltn::c {
	CustomResolver::CustomResolver() {
		auto fx = [] (const std::string & value) {
			return std::make_unique<sst::String>(value);
		};
		this->table.insert({"key", fx});
		this->table.insert({"lang", fx});
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