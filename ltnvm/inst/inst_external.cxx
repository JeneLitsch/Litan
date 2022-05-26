#include "instructions.hxx"
#include "ltnvm/type_check.hxx"
#include <sstream>
namespace ltn::vm::inst {
	void external(VmCore & core) {
		const auto value = core.reg.pop();
		if(is_int(value)) {
			core.reg.push({value.u, Value::Type::EXTERNAL});
		}
		else throw except::invalid_cast("External");
	}
}