#include "GlobalVar.hxx"
#include "ltnc/sst/bind/Binding.hxx"

namespace ltn::c::sst {
	GlobalVar::GlobalVar(std::size_t address)
		: address { address } {}



	std::uint64_t GlobalVar::alloc() const {
		return 0;
	}



	std::unique_ptr<bind::Binding> GlobalVar::convert_to_bindung() && {
		return std::make_unique<bind::Global>(this->address);
	}



	std::unique_ptr<GlobalVar> var_global(std::uint64_t address) {
		return std::make_unique<GlobalVar>(address);
	}
}