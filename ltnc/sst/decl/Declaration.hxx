#pragma once
#include <map>
#include "ltnc/Namespace.hxx"
#include "ltnc/sst/Node.hxx"

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
			std::uint64_t id)
			: Declaration(name, namespaze)
			, id{id} {}
		
		const std::string & get_resolve_name() const {
			return this->name;
		}

		const Namespace & get_resolve_namespace() const {
			return this->namespaze;
		}

		std::uint64_t id;
	};



	struct Definition final : public Static {
		Definition(
			const std::string & name,
			const Namespace & namespaze,
			std::unique_ptr<sst::Expression> expr,
			std::uint64_t id)
			: Static{name, namespaze, id}
			, expr{std::move(expr)} {}
			
		std::unique_ptr<sst::Expression> expr;
	};



	struct Global final : public Static {
		Global(
			const std::string & name,
			const Namespace & namespaze,
			std::unique_ptr<sst::Expression> expr,
			std::uint64_t id)
			: Static{name, namespaze, id}
			, expr{std::move(expr)} {}

		std::unique_ptr<sst::Expression> expr;
	};
}