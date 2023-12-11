#include "ForEach.hxx"
#include "ltnc/sst/expr/Expression.hxx"
#include "ltnc/sst/bind/Binding.hxx"

namespace ltn::c::sst::stmt {
	ForEach::ForEach(
		bind_ptr bind,
		std::size_t container_addr,
		std::size_t iterator_addr,
		expr_ptr expr,
		stmt_ptr body)
		: bind(std::move(bind))
		, container_addr(container_addr)
		, iterator_addr(iterator_addr)
		, expr(std::move(expr))
		, body(std::move(body)) {}



	std::size_t ForEach::nested_alloc() const {
		return body->nested_alloc();
	}
	


	std::size_t ForEach::direct_alloc() const {
		return 2 + this->expr->alloc() + this->bind->alloc_count();
	}



	void ForEach::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}


	
	ForEach::~ForEach() {}



	std::unique_ptr<ForEach> for_each(
		bind_ptr bind,
		std::size_t container_addr,
		std::size_t iterator_addr,
		expr_ptr expr,
		stmt_ptr body) {
		
		return std::make_unique<ForEach>(std::move(bind), container_addr, iterator_addr, std::move(expr), std::move(body));
	}
}