#include "GlobalVar.hxx"
#include "litan_compiler/sst/bind/Global.hxx"
#include "litan_compiler/CompilerError.hxx"

namespace ltn::c::sst::expr {
	GlobalVar::GlobalVar(std::size_t address, bool is_mutable)
		: address { address }
		, is_mutable { is_mutable } {}



	std::uint64_t GlobalVar::alloc() const {
		return 0;
	}



	bind_ptr GlobalVar::convert_to_bindung() && {
		if(this->is_mutable) {
			return bind::global(this->address);
		}
		else {
			throw CompilerError { "Cannot assign definition" };
		}
	}



	std::unique_ptr<GlobalVar> var_global(std::uint64_t address) {
		return std::make_unique<GlobalVar>(address, true);
	}


	std::unique_ptr<GlobalVar> def_global(std::uint64_t address) {
		return std::make_unique<GlobalVar>(address, false);
	}
}