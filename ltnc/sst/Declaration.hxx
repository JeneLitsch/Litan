#pragma once
#include "Node.hxx"
#include "ltnc/Namespace.hxx"
#include <map>
#include "ltnc/type/Type.hxx"

namespace ltn::c::sst {
	struct Expression;
	struct Integer;




	struct Declaration : public Node {
		Declaration(
			const std::string & name,
			const Namespace & namespaze) 
			:	name(name),
				namespaze(namespaze) {}
		virtual ~Declaration() = default;
		std::string name;
		Namespace namespaze;
	};



	struct Static : public Declaration {
		Static(
			const std::string & name,
			const Namespace & namespaze,
			const type::IncompleteType & type) :
				Declaration(name, namespaze),
				id(++counter), type{type} {}
		
		std::uint64_t id;
		type::IncompleteType type;
		const std::string & get_resolve_name() const {
			return this->name;
		}

		const Namespace & get_resolve_namespace() const {
			return this->namespaze;
		}
	private:
		static inline std::uint64_t counter = 0;
	};



	struct Definition final : public Static {
		Definition(
			const std::string & name,
			const Namespace & namespaze,
			const type::IncompleteType & type) :
				Static{name, namespaze, type} {}
		virtual ~Definition() = default;
		std::unique_ptr<sst::Expression> expr;
	};



	struct Global final : public Static {
		Global(
			const std::string & name,
			const Namespace & namespaze,
			const type::IncompleteType & type) :
				Static{name, namespaze,type} {}
		virtual ~Global() = default;
		std::unique_ptr<sst::Expression> expr;
	};
}