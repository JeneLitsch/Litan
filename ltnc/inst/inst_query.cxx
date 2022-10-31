#include "inst.hxx"

namespace ltn::c::inst {
    template<typename InstT>
    std::size_t get_inst_size(const InstT &) {
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
}