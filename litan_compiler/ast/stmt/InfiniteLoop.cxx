#include "InfiniteLoop.hxx"

namespace ltn::c::ast::stmt {
	InfiniteLoop::InfiniteLoop(stmt_ptr body, const SourceLocation & location)
		: Statement(location)
		, body(std::move(body)) {}



	void InfiniteLoop::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}



	InfiniteLoop::~InfiniteLoop() {}



	std::unique_ptr<InfiniteLoop> infinite_loop(stmt_ptr body, const SourceLocation & location) {
		return std::make_unique<InfiniteLoop>(std::move(body), location);
	}
}