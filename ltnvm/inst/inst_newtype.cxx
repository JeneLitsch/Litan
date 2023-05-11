#include "instructions.hxx"
#include "ltnvm/type.hxx"

namespace ltn::vm::inst {
	void newtype(VmCore & core){
		const auto size = core.fetch_uint();
		const auto cstr = core.fetch_str();
		auto [node, end] = make_type(core, cstr);
		std::vector<std::uint8_t> code(cstr, end);
		const auto ptr = core.heap.alloc(Type{
			.code = std::move(code),
			.node = node,
		});
		core.stack.push(value::type(ptr));
		core.pc += size;
		core.heap.collect_garbage(core.stack, core.static_variables);
	}
}