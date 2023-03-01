#pragma once
#include <map>
#include "ltnc/Namespace.hxx"
#include "ltnc/sst/Node.hxx"
#include "ltnc/type/Type.hxx"

namespace ltn::c::sst {
	struct Expression;
	struct Integer;




	struct Declaration : public Node {
		Declaration(
			const std::string & name,
			const Namespace & namespaze) 
			: name(name)
			, namespaze(namespaze) {}

		std::string name;
		Namespace namespaze;
	};



	struct Static : public Declaration {
		Static(
			const std::string & name,
			const Namespace & namespaze,
			const type::Type & type)
			: Declaration(name, namespaze)
			, id(++counter)
			, type{type} {}
		
		const std::string & get_resolve_name() const {
			return this->name;
		}

		const Namespace & get_resolve_namespace() const {
			return this->namespaze;
		}

		std::uint64_t id;
		type::Type type;
	private:
		static inline std::uint64_t counter = 0;
	};



	struct Definition final : public Static {
		Definition(
			const std::string & name,
			const Namespace & namespaze,
			const type::Type & type,
			std::unique_ptr<sst::Expression> expr)
			: Static{name, namespaze, type}
			, expr{std::move(expr)} {}
			
		std::unique_ptr<sst::Expression> expr;
	};



	struct Global final : public Static {
		Global(
			const std::string & name,
			const Namespace & namespaze,
			const type::Type & type,
			std::unique_ptr<sst::Expression> expr)
			: Static{name, namespaze, type}
			, expr{std::move(expr)} {}

		std::unique_ptr<sst::Expression> expr;
	};
}