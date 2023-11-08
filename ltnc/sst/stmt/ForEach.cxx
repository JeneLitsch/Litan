#include "ForEach.hxx"
#include "ltnc/sst/expr/Expression.hxx"

namespace ltn::c::sst {
	ForEach::ForEach(
		std::size_t element_addr,
		std::size_t container_addr,
		std::size_t iterator_addr,
		std::unique_ptr<Expression> expr,
		std::unique_ptr<Statement> body)
		: element_addr(element_addr)
		, container_addr(container_addr)
		, iterator_addr(iterator_addr)
		, expr(std::move(expr))
		, body(std::move(body)) {}



	std::size_t ForEach::nested_alloc() const {
		return body->nested_alloc();
	}
	


	std::size_t ForEach::direct_alloc() const {
		return 3 + this->expr->alloc();
	}



	void ForEach::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}


	
	ForEach::~ForEach() {}



	std::unique_ptr<ForEach> for_each(
		std::size_t element_addr,
		std::size_t container_addr,
		std::size_t iterator_addr,
		std::unique_ptr<Expression> expr,
		std::unique_ptr<Statement> body) {
		
		return std::make_unique<ForEach>(element_addr, container_addr, iterator_addr, std::move(expr), std::move(body));
	}
}