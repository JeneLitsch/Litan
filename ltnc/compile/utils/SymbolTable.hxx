#pragma once
#include <vector>
#include "stdxx/oop.hxx"
#include "ltnc/CompilerError.hxx"
#include "namespace_resolution.hxx"

namespace ltn::c {
	namespace internal {

	}


	// Holds and resolves functions at compile time
	template<typename Symbol>
	class SymbolTable : stx::non_copyable, stx::non_moveable {
	public:
		virtual const Symbol * resolve(
			const std::string_view name,
			const ast::Namespace & from,
			const ast::Namespace & to) = 0;

		virtual const Symbol * resolve(
			const std::string_view name,
			const ast::Namespace & full) = 0;

		virtual void insert(const Symbol & sym) = 0;
	protected:
		SymbolTable() = default;
	};



	// Declaration and usage are allowed.
	template<typename Symbol, typename Err>
	class ValidSymbolTable : public SymbolTable<Symbol> {
	public:

		ValidSymbolTable() = default;
		virtual const Symbol * resolve(
			const std::string_view name,
			const ast::Namespace & from,
			const ast::Namespace & to) {
		
			return ltn::c::resolve(this->symbols, from, to, name);
		}



		virtual const Symbol * resolve(
			const std::string_view name,
			const ast::Namespace & full) {

			for(const auto & symbol : this->symbols) {
				if(symbol->name == name && symbol->namespaze == full) {
					return symbol;
				}
			}
			return nullptr;
		}



		virtual void insert(const Symbol & symbol) {
			// Prevent redefinition
			if(this->resolve(symbol.name, symbol.namespaze)) {
				throw Err::redef(symbol);
			}
			this->symbols.push_back(&symbol);
		}

	private:
		std::vector<const Symbol *> symbols;
	};



	// Declaration and usage are prohibited.
	template<typename Symbol, typename Err>
	class InvalidSymbolTable : public SymbolTable<Symbol> {
	public:

		InvalidSymbolTable(const std::string & inside) 
			: inside { inside } {}



		virtual const Symbol * resolve(
			const std::string_view,
			const ast::Namespace &,
			const ast::Namespace &) override {
			throw Err::use(this->inside);
		}



		virtual const Symbol * resolve(
			const std::string_view,
			const ast::Namespace &) override {
			throw Err::use(this->inside);
		}



		virtual void insert(const Symbol &) override {
			throw Err::decl(this->inside);
		}

	private:
		std::string inside;
	};
}