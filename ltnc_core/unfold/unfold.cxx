#include "unfold.hxx"

namespace ltn::c::unfold {
	void program(ast::Program & program) {
		for(auto & preset : program.presets) {
			auto ctor = unfold::preset(std::move(preset));
			program.functions.push_back(std::move(ctor));
		}
		program.presets.clear();
	}
}