#include "instructions.hxx"

namespace ltn::vm::inst {
	namespace {
		void reserve_static(auto & global_variabls, auto id) {
			if(global_variabls.size() <= id) {
				global_variabls.resize(id + 1, value::null);
			}
		}
	}
	

	
	void static_read(VmCore & core) {
		const auto id = core.fetch_uint();
		// std::cout << "GLOBAL_READ:" << id << "\n";
		reserve_static(core.static_variables, id);
		core.stack.push(core.static_variables[id]);
	}



	void static_write(VmCore & core) {
		const auto id = core.fetch_uint();
		// std::cout << "GLOBAL_WRITE:" << id << "\n";
		const auto value = core.stack.pop();
		reserve_static(core.static_variables, id);
		core.static_variables[id] = value;
	}
}