#include "scan.hxx"
#include <stdexcept>

namespace ltn::a {
	AddressTable scan(const std::vector<inst::Instruction> & instructions) {
		std::size_t position = 0;
		AddressTable table;
		for(const auto & inst : instructions) {
			auto get_size = [] (auto & args) {
				return inst::args::size(args);
			};
			position += std::visit(get_size, inst.args);
			if(auto label = std::get_if<inst::args::Target>(&inst.args)) {
				if(table.contains(label->name)) throw std::runtime_error {
					"Redefinition of label " + label->name
				};
				table.insert({label->name, position});
			}
		}
		return table;
	}
}