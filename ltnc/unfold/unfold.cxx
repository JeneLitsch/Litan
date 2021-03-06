#include "unfold.hxx"

namespace ltn::c {
	ast::prog_ptr unfold_source(ast::srce_ptr source) {
		auto t_unit = std::make_unique<ast::Program>();

		t_unit->functions = std::move(source->functions);
		t_unit->globals = std::move(source->globals);

		for(auto & preset : source->presets) {
			auto ctor = unfold_preset(std::move(preset));
			t_unit->functions.push_back(std::move(ctor));
		}

		for(auto & enym : source->enums) {
			auto globals = unfold_enumeration(std::move(enym));
			for(auto & global : globals) {
				t_unit->globals.push_back(std::move(global));
			}
		}

		return t_unit;
	}
}