#pragma once
#include "Statement.hxx"

namespace ltn::c::sst::stmt {
	struct ForEach final : public Statement {
		ForEach(
			std::size_t element_addr,
			std::size_t container_addr,
			std::size_t iterator_addr,
			expr_ptr expr,
			stmt_ptr body);

		virtual std::size_t nested_alloc() const override;
		virtual std::size_t direct_alloc() const override;
		virtual void accept(const StmtVisitor & visitor) const override;

		virtual ~ForEach();

		std::size_t element_addr;
		std::size_t container_addr;
		std::size_t iterator_addr;
		expr_ptr expr;
		stmt_ptr body;
	};

	std::unique_ptr<ForEach> for_each(
		std::size_t element_addr,
		std::size_t container_addr,
		std::size_t iterator_addr,
		expr_ptr expr,
		stmt_ptr body);
}