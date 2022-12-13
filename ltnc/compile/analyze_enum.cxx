#include "compile.hxx"

namespace ltn::c {
	std::vector<sst::defn_ptr> analyze_enumeration(const ast::Enumeration & enumeration) {
		auto namespaze = enumeration.namespaze;
		namespaze.push_back(enumeration.name);

		std::vector<sst::defn_ptr> defintions;
		for(auto & [name, value] : enumeration.labels) {
			auto defintion = stx::make_unique<sst::Definition>(
				value->location,
				name,
				namespaze,
				type::IncompleteType{type::Int{}}
			); 
			defintion->expr = stx::make_unique<sst::Integer>(value->value, value->location);
			defintions.push_back(std::move(defintion));
		}
		return defintions;
	}
}