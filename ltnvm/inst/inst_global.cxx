#include "instructions.hxx"

namespace ltn::vm::inst {
	namespace {
		void reserve_globals(auto & global_variabls, auto id) {
			if(global_variabls.size() <= id) {
				global_variabls.resize(id + 1, value::null);
			}
		}
	}
	
	void global_read(VmCore & core) {
		const auto id = core.fetch_uint();
		reserve_globals(core.global_variables, id);
		core.reg.push(core.global_variables[id]);
		// std::cout << "GLOBAL READ\n";
	}

	void global_write(VmCore & core) {
		const auto id = core.fetch_uint();
		const auto value = core.reg.pop();
		reserve_globals(core.global_variables, id);
		core.global_variables[id] = value;
		// std::cout << "GLOBAL WRITE\n";
	}
}