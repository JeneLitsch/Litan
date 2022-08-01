#pragma once
#include "ltnc/ast/Ast.hxx"
#include <vector>
#include "stdxx/oop.hxx"
namespace ltn::c {
	// Holds and resolves functions at compile time
	class DefinitionTable : stx::non_copyable, stx::non_moveable {
	public:
		virtual const ast::Definition * resolve(
			const std::string_view name,
			const ast::Namespace & from,
			const ast::Namespace & to) = 0;

		virtual const ast::Definition * resolve(
			const std::string_view name,
			const ast::Namespace & full) = 0;

		virtual void insert(const ast::Definition & fx) = 0;
	protected:
		DefinitionTable() = default;
	};



	// Defintions are allowed.
	class ValidDefinitionTable : public DefinitionTable {
	public:
		ValidDefinitionTable() = default;
		virtual const ast::Definition * resolve(
			const std::string_view name,
			const ast::Namespace & from,
			const ast::Namespace & to);

		virtual const ast::Definition * resolve(
			const std::string_view name,
			const ast::Namespace & full);

		virtual void insert(const ast::Definition & fx);
	private:
		std::vector<const ast::Definition *> enums;
	};



	// Defintions are prohibited.
	class InvalidDefinitionTable : public DefinitionTable {
	public:
		InvalidDefinitionTable(const std::string & inside) : inside { inside } {}
		virtual const ast::Definition * resolve(
			const std::string_view name,
			const ast::Namespace & from,
			const ast::Namespace & to);

		virtual const ast::Definition * resolve(
			const std::string_view name,
			const ast::Namespace & full);

		virtual void insert(const ast::Definition & fx);
	private:
		std::string inside;
	};
}