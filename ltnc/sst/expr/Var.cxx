#include "Var.hxx"
#include "ltnc/sst/bind/Binding.hxx"

namespace ltn::c::sst {
	Var::Var(std::size_t address)
		: address{address} {}



	std::uint64_t Var::alloc() const {
		return 0;
	}



	std::unique_ptr<Binding> Var::convert_to_bindung() && {
		return std::make_unique<NewVarBinding>(this->address);
	}
}