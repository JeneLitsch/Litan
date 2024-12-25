#pragma once
#include "Statement.hxx"

namespace ltn::c::sst::stmt {
	struct ForEach final : public Statement {
		ForEach(
			bind_ptr bind,
			std::size_t container_addr,
			std::size_t iterator_addr,
			expr_ptr expr,
			stmt_ptr body);

		virtual std::size_t temporary_alloc() const override;
		virtual std::size_t persistent_alloc() const override;
		virtual void accept(const StmtVisitor & visitor) const override;

		virtual ~ForEach();

		bind_ptr bind;
		std::size_t container_addr;
		std::size_t iterator_addr;
		expr_ptr expr;
		stmt_ptr body;
	};

	std::unique_ptr<ForEach> for_each(
		bind_ptr bind,
		std::size_t container_addr,
		std::size_t iterator_addr,
		expr_ptr expr,
		stmt_ptr body);
}