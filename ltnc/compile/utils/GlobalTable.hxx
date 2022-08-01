#pragma once
#include <unordered_map>
#include <cstdint>
#include <string>
#include "ltnc/ast/Ast.hxx"
#include "stdxx/oop.hxx"

namespace ltn::c {
	class GlobalTable : stx::non_copyable, stx::non_moveable {
	public:
		virtual const ast::Global * resolve(
			const std::string_view name,
			const ast::Namespace & from,
			const ast::Namespace & to) = 0;

		virtual const ast::Global * resolve(
			const std::string_view name,
			const ast::Namespace & full) = 0;

		virtual void insert(const ast::Global & fx) = 0;
	protected:
		GlobalTable() = default;
	};



	class ValidGlobalTable : public GlobalTable {
	public:
		ValidGlobalTable() = default;
		virtual const ast::Global * resolve(
			const std::string_view name,
			const ast::Namespace & from,
			const ast::Namespace & to) override;

		virtual const ast::Global * resolve(
			const std::string_view name,
			const ast::Namespace & full) override;

		virtual void insert(const ast::Global & fx) override;
	private:
		std::vector<const ast::Global *> enums;
	};



	class InvalidGlobalTable : public GlobalTable {
	public:
		InvalidGlobalTable(const std::string & inside) : inside { inside } {};
		virtual const ast::Global * resolve(
			const std::string_view name,
			const ast::Namespace & from,
			const ast::Namespace & to) override;

		virtual const ast::Global * resolve(
			const std::string_view name,
			const ast::Namespace & full) override;

		virtual void insert(const ast::Global & fx) override;
	private:
		std::string inside;
	};
}