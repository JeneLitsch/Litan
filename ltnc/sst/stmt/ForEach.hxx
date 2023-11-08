#pragma once
#include "Statement.hxx"

namespace ltn::c::sst {
	struct Expression;
	struct ForEach final : public Statement {
		ForEach(
			std::size_t element_addr,
			std::size_t container_addr,
			std::size_t iterator_addr,
			std::unique_ptr<Expression> expr,
			std::unique_ptr<Statement> body);

		virtual std::size_t nested_alloc() const override;
		virtual std::size_t direct_alloc() const override;
		virtual void accept(const StmtVisitor & visitor) const override;

		virtual ~ForEach();

		std::size_t element_addr;
		std::size_t container_addr;
		std::size_t iterator_addr;
		std::unique_ptr<Expression> expr;
		std::unique_ptr<Statement> body;
	};

	std::unique_ptr<ForEach> for_each(
		std::size_t element_addr,
		std::size_t container_addr,
		std::size_t iterator_addr,
		std::unique_ptr<Expression> expr,
		std::unique_ptr<Statement> body);
}