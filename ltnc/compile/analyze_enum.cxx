#include "compile.hxx"

namespace ltn::c {
	std::vector<sst::defn_ptr> analyze_enumeration(const ast::Enumeration & enumeration) {
		auto namespaze = enumeration.namespaze;
		namespaze.push_back(enumeration.name);

		std::vector<sst::defn_ptr> defintions;
		for(auto & [name, value] : enumeration.labels) {
			auto defintion = std::make_unique<sst::Definition>(
				name,
				namespaze,
				type::Int{}
			); 
			defintion->expr = std::make_unique<sst::Integer>(value->value, type::Int{});
			defintions.push_back(std::move(defintion));
		}
		return defintions;
	}
}