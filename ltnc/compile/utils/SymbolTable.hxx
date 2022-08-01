#pragma once
#include <vector>
#include "stdxx/oop.hxx"
#include "ltnc/CompilerError.hxx"
#include "namespace_resolution.hxx"

namespace ltn::c {
	// Holds and resolves functions at compile time
	template<typename Symbol, typename ... Args>
	class SymbolTable : stx::non_copyable, stx::non_moveable {
	public:
		virtual const Symbol * resolve(
			const std::string_view name,
			const ast::Namespace & from,
			const ast::Namespace & to,
			Args ... args) = 0;

		virtual const Symbol * resolve(
			const std::string_view name,
			const ast::Namespace & full,
			Args ... args) = 0;

		virtual void insert(
			const Symbol & sym,
			Args ... args) = 0;
	protected:
		SymbolTable() = default;
	};



	// Declaration and usage are allowed.
	template<typename Symbol, typename Err, typename ... Args>
	class ValidSymbolTable : public SymbolTable<Symbol, Args...> {
	public:

		ValidSymbolTable() = default;
		virtual const Symbol * resolve(
			const std::string_view name,
			const ast::Namespace & from,
			const ast::Namespace & to,
			Args ... args) {
		
			return ltn::c::resolve(this->symbols, from, to, name, args...);
		}



		virtual const Symbol * resolve(
			const std::string_view name,
			const ast::Namespace & full,
			Args ... args) {

			return ltn::c::resolve(this->symbols, {}, full, name, args...);
		}



		virtual void insert(
			const Symbol & symbol,
			Args ... args) {
			// Prevent redefinition
			if(this->resolve(symbol.name, symbol.namespaze, args...)) {
				throw Err::redef(symbol);
			}
			this->symbols.push_back(&symbol);
		}

	private:
		std::vector<const Symbol *> symbols;
	};



	// Declaration and usage are prohibited.
	template<typename Symbol, typename Err, typename ... Args>
	class InvalidSymbolTable : public SymbolTable<Symbol, Args...> {
	public:

		InvalidSymbolTable(const std::string & inside) 
			: inside { inside } {}



		virtual const Symbol * resolve(
			const std::string_view,
			const ast::Namespace &,
			const ast::Namespace &,
			Args ...) override {
			throw Err::use(this->inside);
		}



		virtual const Symbol * resolve(
			const std::string_view,
			const ast::Namespace &,
			Args ...) override {
			throw Err::use(this->inside);
		}



		virtual void insert(
			const Symbol &,
			Args ...) override {
			throw Err::decl(this->inside);
		}

	private:
		std::string inside;
	};
}