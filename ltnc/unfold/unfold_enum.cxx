#include "unfold.hxx"

namespace ltn::c {
	std::vector<ast::glob_ptr> unfold_enumeration(ast::enum_ptr e) {
		auto namespaze = e->namespaze;
		namespaze.push_back(e->name);

		std::vector<ast::glob_ptr> globals;
		for(auto & [name, value] : e->labels) {
			auto global = std::make_unique<ast::Global>(
				value->location,
				name,
				namespaze); 
			global->expr = std::move(value);
			globals.push_back(std::move(global));
		}
		return globals;
	}
}