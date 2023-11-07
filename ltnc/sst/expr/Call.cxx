#include "Call.hxx"

namespace ltn::c::sst {
	Call::Call(const Label & label, std::vector<expr_ptr> arguments)
		: label{label}
		, arguments(std::move(arguments)) {}

	
	
	std::uint64_t Call::alloc() const {
		std::uint64_t count = 0;
		for(const auto & elem : this->arguments) {
			count = std::max(elem->alloc(), count);
		}
		return count;
	}



	std::uint64_t Call::arity() const {
		return std::size(arguments);
	}
}