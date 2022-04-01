#include "unfold.hxx"

namespace ltn::c::unfold {
	ast::prog_ptr source(ast::srce_ptr source) {
		auto t_unit = std::make_unique<ast::Program>();

		t_unit->functions = std::move(source->functions);
		t_unit->globals = std::move(source->globals);

		for(auto & preset : source->presets) {
			auto ctor = unfold::preset(std::move(preset));
			t_unit->functions.push_back(std::move(ctor));
		}

		for(auto & enym : source->enums) {
			auto globals = unfold::enumeration(std::move(enym));
			for(auto & global : globals) {
				t_unit->globals.push_back(std::move(global));
			}
		}

		return t_unit;
	}
}