#include "linking.hxx"

namespace ltn::a::linking {
	bool is_jumpmark(std::string_view inst) {
		return inst[0] == ':';
	}
}