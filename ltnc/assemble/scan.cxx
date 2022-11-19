#include "scan.hxx"
#include <stdexcept>

namespace ltn::c {
    template<typename InstT>
    std::size_t get_inst_size(const InstT &) {
        return InstT::size;
    }

    std::size_t get_inst_size(const inst::InstUint64Bytex & inst) {
        return 1 + 8 + inst.bytes.size();
    }

    std::size_t get_inst_size(const inst::InstBytex0 & inst) {
        return 1 + inst.bytes.size() + 1;
    }

	std::size_t size(const inst::Inst & inst) {
        return std::visit([](auto & i) {
            return get_inst_size(i);
        }, inst);
    }

	AddressTable scan(const std::vector<inst::Inst> & instructions) {
		std::size_t position = 0;
		AddressTable table;
		for(const auto & inst : instructions) {
			position += size(inst);
			if(auto label = std::get_if<inst::InstLabel>(&inst)) {
				if(table.contains(label->label)) throw std::runtime_error {
					"Redefinition of label " + std::string(label->label)
				};
				table.insert({label->label, position});
			}
		}
		return table;
	}
}