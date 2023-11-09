#pragma once
#include "Expression.hxx"

namespace ltn::c::sst::expr {
	struct Iife final : public ExpressionCRTP<Iife> {
		Iife(std::string return_label, std::unique_ptr<stmt::Statement> stmt);

		virtual std::uint64_t alloc() const override;

		std::string return_label;
		std::unique_ptr<stmt::Statement> stmt;
	};

	std::unique_ptr<Iife> iife(std::string return_label, std::unique_ptr<stmt::Statement> stmt);
}