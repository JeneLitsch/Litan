#include "scan.hxx"
#include <stdexcept>
namespace ltn::a {
	AddressTable scan(const std::vector<inst::Instruction> & instructions) {
		std::size_t position = 0;
		AddressTable table;
		for(const auto & inst : instructions) {
			auto get_size = [] (auto & inst) {
				return inst::args::size(inst.args);
			};
			position += std::visit(get_size, inst);
			if(auto label = std::get_if<inst::Label>(&inst)) {
				if(table.contains(label->args.name)) throw std::runtime_error {
					"Redefinition of label " + label->args.name
				};
				table.insert({label->args.name, position});
			}
		}
		return table;
	}
}