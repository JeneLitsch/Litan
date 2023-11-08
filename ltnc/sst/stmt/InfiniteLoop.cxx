#include "InfiniteLoop.hxx"

namespace ltn::c::sst {
	InfiniteLoop::InfiniteLoop(
		std::unique_ptr<Statement> body)
		: Statement{}
		, body(std::move(body)) {}

	std::size_t InfiniteLoop::nested_alloc() const {
		return body->nested_alloc();
	}
	
	std::size_t InfiniteLoop::direct_alloc() const {
		return 0;
	}

	void InfiniteLoop::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}

	std::unique_ptr<InfiniteLoop> infinite_loop(std::unique_ptr<Statement> body) {
		return std::make_unique<InfiniteLoop>(std::move(body));
	}
}