#include "Var.hxx"
#include "ltnc/sst/bind/Binding.hxx"

namespace ltn::c::sst::expr {
	Var::Var(std::size_t address)
		: address{address} {}



	std::uint64_t Var::alloc() const {
		return 0;
	}



	bind_ptr Var::convert_to_bindung() && {
		return std::make_unique<bind::NewVar>(this->address);
	}



	std::unique_ptr<Var> var_local(std::uint64_t address) {
		return std::make_unique<Var>(address);
	}
}