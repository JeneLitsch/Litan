#pragma once
#include <cstdint>
#include <set>
#include <memory>
#include <variant>

#include "LtncFunction.hxx"
#include "LtncType.hxx"
#include "LtncVar.hxx"
namespace ltnc {
	
	class Scope {
	public:
		Scope(Scope & scope);
		Scope(Scope & scope, const FunctionSignature & signature);
		Scope();
		
		std::uint32_t countVars() const;
		const FunctionSignature & getFxSignature() const;

		typedef std::variant<
			Type,
			Function,
			Var
		> Entry;

		template<class Searched, class Searcher>
		const Searched * find(const Searcher & searcher, bool fallthrough = true) const {
			for(const Entry & entry : table) {
				if(const Searched * value = std::visit(searcher, entry)) {
					return value;
				}
			}
			if(this->prev && fallthrough) {
				return this->prev->find<Searched, Searcher>(searcher, true);
			}
			return nullptr;
		}

		void add(const Type & entry);
		void add(const Function & entry);
		void add(const Var & entry);


	private:
		unsigned counterVars;
		unsigned counterTypes;
		unsigned counterFuncs;

		std::vector<Entry> table;
		std::optional<FunctionSignature> fxSignature;
		Scope * prev;
	};

}