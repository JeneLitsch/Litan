#include "instructions.hxx"
#include "ltnvm/utils/type_check.hxx"
#include "ltnvm/Exception.hxx"

namespace ltn::vm::inst {
	void ref_read(VmCore & core) {
		auto ref = core.stack.pop();
		if(is_stack_ref(ref)) {
			core.stack.push(core.stack.read_absolute(ref.u));
			return;
		}
		throw except::invalid_argument("Not a ref. Cannot read.");
	}



	void ref_write(VmCore & core) {
		auto ref = core.stack.pop();
		auto value = core.stack.pop();
		if(is_stack_ref(ref)) {
			core.stack.write_absolute(ref.u, value);
			return;
		}
		throw except::invalid_argument("Not a ref. Cannot write.");
	}



	void newref_local(VmCore & core) {
		auto local_address = core.fetch_uint();
		auto global_address = core.stack.local_to_global_address(local_address);
		core.stack.push(value::stack_ref(global_address));
	}
}