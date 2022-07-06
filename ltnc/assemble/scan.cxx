#include "scan.hxx"
#include <stdexcept>

namespace ltn::c {
	AddressTable scan(const std::vector<inst::Instruction> & instructions) {
		std::size_t position = 0;
		AddressTable table;
		for(const auto & inst : instructions) {
			auto get_size = [] (auto & args) {
				return inst::args::size(args);
			};
			const auto args = inst.args();
			position += std::visit(get_size, args);
			if(auto label = inst.as<inst::Label>()) {
				if(table.contains(label->args.name)) throw std::runtime_error {
					"Redefinition of label " + std::string(label->args.name)
				};
				table.insert({label->args.name, position});
			}
		}
		return table;
	}
}