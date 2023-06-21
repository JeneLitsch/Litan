#pragma once
#include <ostream>

namespace ltn::c::trans {
	struct Indent {
		std::uint64_t indent = 0;
		Indent in() {
			return Indent {
				.indent = this->indent + 1,
			};
		} 
	};

	inline std::ostream & operator<<(std::ostream & out, const Indent & indent) {
		for(std::uint64_t i = 0; i < indent.indent; ++i) {
			out << "\t";
		}
		return out;
	}
}