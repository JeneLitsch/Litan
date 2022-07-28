#include "unfold.hxx"

namespace ltn::c {
	ast::prog_ptr unfold_source(ast::srce_ptr source) {
		auto t_unit = std::make_unique<ast::Program>();

		t_unit->functions = std::move(source->functions);
		t_unit->definitions = std::move(source->definitions);

		for(auto & preset : source->presets) {
			auto ctor = unfold_preset(std::move(preset));
			t_unit->functions.push_back(std::move(ctor));
		}

		for(auto & enym : source->enums) {
			auto definitions = unfold_enumeration(std::move(enym));
			for(auto & definition : definitions) {
				t_unit->definitions.push_back(std::move(definition));
			}
		}

		return t_unit;
	}
}