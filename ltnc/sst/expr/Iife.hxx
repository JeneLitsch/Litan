#pragma once
#include "Expression.hxx"

namespace ltn::c::sst {
	class Statement;
	struct Iife final : public ExpressionCRTP<Iife> {
		Iife(std::string return_label, std::unique_ptr<Statement> stmt);

		virtual std::uint64_t alloc() const override;

		std::string return_label;
		std::unique_ptr<Statement> stmt;
	};

	std::unique_ptr<Iife> iife(std::string return_label, std::unique_ptr<Statement> stmt);
}