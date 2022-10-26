#include "inst.hxx"

namespace ltn::c::inst {
    template<typename InstT>
    std::size_t get_inst_size(const InstT & inst) {
        return InstT::size;
    }

    std::size_t get_inst_size(const InstUint64Bytex & inst) {
        return 1 + 8 + inst.bytes.size();
    }

    std::size_t get_inst_size(const InstBytex0 & inst) {
        return 1 + inst.bytes.size() + 1;
    }

	std::size_t inst_size(const Inst & inst) {
        return std::visit([](auto & i) {
            return get_inst_size(i);
        }, inst);
    }

	

	template<typename InstT>
    std::string_view get_inst_name(const InstT & inst) {
        return inst.name;
    }
	
    std::string_view name(const Inst & inst) {
        return std::visit([](auto & i) {
            return get_inst_name(i);
        }, inst);
    }



	template<typename InstT>
    OpCode get_inst_opcode(const InstT & inst) {
        return inst.opcode;
    }

	OpCode opcode(const Inst & inst) {
        return std::visit([](auto & i) {
            return get_inst_opcode(i);
        }, inst);
    }
}