#include "instructions.hxx"
#include "ltnvm/type_check.hxx"
#include <sstream>
namespace ltn::vm::inst {
	void external(VmCore & core) {
		const auto value = core.stack.pop();
		if(is_int(value)) {
			core.stack.push({value.u, Value::Type::EXTERNAL});
		}
		else throw except::invalid_cast("External");
	}
}