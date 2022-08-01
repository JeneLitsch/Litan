#pragma once
#include "ltnc/ast/Ast.hxx"
#include <vector>
#include "stdxx/oop.hxx"
namespace ltn::c {
	// Holds and resolves functions at compile time
	class FxTable : stx::non_copyable, stx::non_moveable {
	public:
		virtual const ast::Functional * resolve(
			const std::string_view name,
			const ast::Namespace & from,
			const ast::Namespace & to,
			const std::size_t parameters) = 0;

		virtual const ast::Functional * resolve(
			const std::string_view name,
			const ast::Namespace & full,
			const std::size_t parameters) = 0;

		virtual void insert(const ast::Functional & fx) = 0;
	protected:
		FxTable() = default;
	};


	
	class ValidFxTable : public FxTable {
	public:
		ValidFxTable() = default;
		
		virtual const ast::Functional * resolve(
			const std::string_view name,
			const ast::Namespace & from,
			const ast::Namespace & to,
			const std::size_t parameters) override;

		virtual const ast::Functional * resolve(
			const std::string_view name,
			const ast::Namespace & full,
			const std::size_t parameters) override;

		virtual void insert(const ast::Functional & fx) override;
	private:
		std::vector<const ast::Functional *> functions;
	};



	class InvalidFxTable : public FxTable {
	public:
		InvalidFxTable(const std::string & inside) : inside { inside } {}
		
		virtual const ast::Functional * resolve(
			const std::string_view name,
			const ast::Namespace & from,
			const ast::Namespace & to,
			const std::size_t parameters) override;

		virtual const ast::Functional * resolve(
			const std::string_view name,
			const ast::Namespace & full,
			const std::size_t parameters) override;

		virtual void insert(const ast::Functional & fx) override;
	private:
		std::string inside;
	};
}