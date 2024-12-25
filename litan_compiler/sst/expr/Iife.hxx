#pragma once
#include "Expression.hxx"

namespace ltn::c::sst::expr {
	struct Iife final : public ExpressionCRTP<Iife> {
		Iife(std::string return_label, stmt_ptr stmt);

		virtual std::uint64_t alloc() const override;

		std::string return_label;
		stmt_ptr stmt;
	};

	std::unique_ptr<Iife> iife(std::string return_label, stmt_ptr stmt);
}