#pragma once
#include "Node.hxx"
#include "Namespace.hxx"
#include <map>
#include "ltnc/type/Type.hxx"

namespace ltn::c::ast {
	struct Expression;
	struct Integer;




	struct Declaration : public Node {
		Declaration(
			const SourceLocation & location,
			const std::string & name,
			const Namespace & namespaze) 
			:	Node(location),
				name(name),
				namespaze(namespaze) {}
		virtual ~Declaration() = default;
		std::string name;
		Namespace namespaze;
	};



	struct Static : public Declaration {
		Static(
			const SourceLocation & location,
			const std::string & name,
			const Namespace & namespaze,
			const type::IncompleteType & type) :
				Declaration(location, name, namespaze),
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
			const SourceLocation & location,
			const std::string & name,
			const Namespace & namespaze,
			const type::IncompleteType & type) :
				Static{location, name, namespaze, type} {}
		virtual ~Definition() = default;
		std::unique_ptr<ast::Expression> expr;
	};



	struct Global final : public Static {
		Global(
			const SourceLocation & location,
			const std::string & name,
			const Namespace & namespaze,
			const type::IncompleteType & type) :
				Static{location, name, namespaze,type} {}
		virtual ~Global() = default;
		std::unique_ptr<ast::Expression> expr;
	};



	struct Preset final : public Declaration {
		struct Member {
			std::string name;
			type::IncompleteType type;
		};

		Preset(
			const SourceLocation & location,
			const std::string & name,
			const Namespace & namespaze,
			const std::vector<Member> & members)
			:	Declaration(location, name, namespaze),
				members(members) {}
		virtual ~Preset() = default;
		std::vector<Member> members;

		const std::string & get_resolve_name() const {
			return this->name;
		}

		const Namespace & get_resolve_namespace() const {
			return this->namespaze;
		}
	};


	
	struct Enumeration final : public Declaration {
		struct Label {
			std::string name;
			std::unique_ptr<ast::Integer> value;
		};
		
		Enumeration(
			const SourceLocation & location,
			const std::string & name,
			const Namespace & namespaze)
			:	Declaration(location, name, namespaze) {}
		virtual ~Enumeration() = default;
		std::vector<Label> labels;
	};
}