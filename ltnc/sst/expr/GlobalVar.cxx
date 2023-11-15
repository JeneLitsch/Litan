#include "GlobalVar.hxx"
#include "ltnc/sst/bind/Global.hxx"

namespace ltn::c::sst::expr {
	GlobalVar::GlobalVar(std::size_t address)
		: address { address } {}



	std::uint64_t GlobalVar::alloc() const {
		return 0;
	}



	bind_ptr GlobalVar::convert_to_bindung() && {
		return bind::global(this->address);
	}



	std::unique_ptr<GlobalVar> var_global(std::uint64_t address) {
		return std::make_unique<GlobalVar>(address);
	}
}