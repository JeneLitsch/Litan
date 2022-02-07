#include "linking.hxx"

namespace ltn::a::linking {
	bool isJumpMark(std::string_view inst) {
		return inst[0] == ':';
	}
}