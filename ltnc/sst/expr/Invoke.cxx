#include "Invoke.hxx"

namespace ltn::c::sst {
	Invoke::Invoke(expr_ptr function_ptr, std::vector<expr_ptr> arguments)
		: function_ptr(std::move(function_ptr))
		, arguments(std::move(arguments)) {}



	std::uint64_t Invoke::alloc() const {
		std::uint64_t count = 0;
		for(const auto & elem : this->arguments) {
			count = std::max(elem->alloc(), count);
		}
		return std::max(count, function_ptr->alloc());
	}



	std::uint64_t Invoke::arity() const {
		return std::size(arguments);
	}



	std::unique_ptr<Invoke> invoke(expr_ptr function_ptr, std::vector<expr_ptr> arguments) {
		return std::make_unique<Invoke>(std::move(function_ptr), std::move(arguments));
	}
}