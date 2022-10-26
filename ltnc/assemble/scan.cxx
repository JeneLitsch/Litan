#include "scan.hxx"
#include <stdexcept>

namespace ltn::c {
	AddressTable scan(const std::vector<inst::Inst> & instructions) {
		std::size_t position = 0;
		AddressTable table;
		for(const auto & inst : instructions) {
			position += inst::inst_size(inst);
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