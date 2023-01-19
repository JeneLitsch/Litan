#include "Language.hxx"

namespace ltn::c::lang {
	std::string Language::indent(unsigned indentation) const {
		return std::string(indentation, '\t');
	}
}