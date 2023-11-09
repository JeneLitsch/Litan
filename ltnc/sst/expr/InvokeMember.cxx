#include "InvokeMember.hxx"

namespace ltn::c::sst::expr {
	InvokeMember::InvokeMember(
		expr_ptr object,
		std::uint64_t member_id,
		std::vector<expr_ptr> arguments)
		: object(std::move(object))
		, member_id{member_id}
		, arguments(std::move(arguments)) {}



	std::uint64_t InvokeMember::alloc() const {
		std::uint64_t count = 0;
		for(const auto & elem : this->arguments) {
			count = std::max(elem->alloc(), count);
		}
		return std::max(count, object->alloc());
	}



	std::uint64_t InvokeMember::arity() const {
		return std::size(arguments) + 1;
	}



	std::unique_ptr<InvokeMember> invoke_member(expr_ptr object, std::uint64_t member_id, std::vector<expr_ptr> arguments) {
		return std::make_unique<InvokeMember>(std::move(object), member_id, std::move(arguments));
	}
}