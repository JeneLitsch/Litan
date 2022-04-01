#include "unfold.hxx"

namespace ltn::c::unfold {
	void program(ast::Source & source) {
		for(auto & preset : source.presets) {
			auto ctor = unfold::preset(std::move(preset));
			source.functions.push_back(std::move(ctor));
		}
		source.presets.clear();
	}
}