#include "ForEach.hxx"
#include "litan_compiler/sst/expr/Expression.hxx"
#include "litan_compiler/sst/bind/Binding.hxx"

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



	std::size_t ForEach::temporary_alloc() const {
		return 2 + this->expr->alloc() + this->bind->alloc_count() + body->total_alloc();
	}
	


	std::size_t ForEach::persistent_alloc() const {
		// No persistent allocation
		// No variable in head or body leaks to the outside scope 
		return 0;
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