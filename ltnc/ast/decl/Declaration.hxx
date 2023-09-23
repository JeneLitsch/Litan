#pragma once
#include <map>
#include "ltnc/Namespace.hxx"
#include "ltnc/ast/Node.hxx"

namespace ltn::c::ast {
	struct Expression;
	struct Integer;



	struct Declaration : public Node {
		Declaration(
			const SourceLocation & location,
			const std::string & name,
			const Namespace & namespaze) 
			: Node(location)
			, name(name)
			, namespaze(namespaze) {}
		virtual ~Declaration() = default;
		std::string name;
		Namespace namespaze;
	};



	struct Static : public Declaration {
		Static(
			const SourceLocation & location,
			const std::string & name,
			const Namespace & namespaze)
			: Declaration(location, name, namespaze)
			, id(++counter) {}
		
		std::uint64_t id;
		const std::string & get_resolve_name() const {
			return this->name;
		}

		const Namespace & get_resolve_namespace() const {
			return this->namespaze;
		}

		bool is_extern = false;
		bool is_private = false;
	private:
		static inline std::uint64_t counter = 0;
	};



	struct Definition final : public Static {
		Definition(
			const SourceLocation & location,
			const std::string & name,
			const Namespace & namespaze)
			: Static{location, name, namespaze} {}
		virtual ~Definition() = default;
		std::unique_ptr<ast::Expression> expr;
	};



	struct Global final : public Static {
		Global(
			const SourceLocation & location,
			const std::string & name,
			const Namespace & namespaze)
			: Static{location, name, namespaze} {}
		virtual ~Global() = default;
		std::unique_ptr<ast::Expression> expr;
	};


	
	struct Enumeration final : public Declaration {
		struct Label {
			std::string name;
			std::int64_t value;
		};
		
		Enumeration(
			const SourceLocation & location,
			const std::string & name,
			const Namespace & namespaze,
			std::vector<Label> labels)
			: Declaration(location, name, namespaze)
			, labels{std::move(labels)} {}
		virtual ~Enumeration() = default;
		std::vector<Label> labels;
	};
}