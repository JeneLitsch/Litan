#include "analyze.hxx"
#include "stdxx/functional.hxx"

namespace ltn::c {
	std::vector<sst::defn_ptr> analyze_enumeration(const ast::Enumeration & enumeration) {

		auto namespaze = enumeration.namespaze;
		namespaze.push_back(enumeration.name);

		return stx::fx::mapped([&] (const auto & label) {
			return std::make_unique<sst::Definition>(
				label.name, namespaze, type::Int{},
				std::make_unique<sst::Integer>(label.value, type::Int{})
			);
		}) (enumeration.labels);
	}
}