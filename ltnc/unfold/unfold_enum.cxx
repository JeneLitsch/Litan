#include "unfold.hxx"

namespace ltn::c {
	std::vector<ast::defn_ptr> unfold_enumeration(ast::enum_ptr e) {
		auto namespaze = e->namespaze;
		namespaze.push_back(e->name);

		std::vector<ast::defn_ptr> defintions;
		for(auto & [name, value] : e->labels) {
			auto defintion = std::make_unique<ast::Definition>(
				value->location,
				name,
				namespaze); 
			defintion->expr = std::move(value);
			defintions.push_back(std::move(defintion));
		}
		return defintions;
	}
}