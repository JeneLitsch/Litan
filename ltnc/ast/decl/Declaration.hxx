#pragma once
#include "../Node.hxx"
#include "../Namespace.hxx"
#include <map>

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
			const Namespace & namespaze) :
				Declaration(location, name, namespaze),
				id(++counter) {}
		
		std::uint64_t id;
	private:
		static inline std::uint64_t counter = 0;
	};



	struct Definition final : public Static {
		Definition(
			const SourceLocation & location,
			const std::string & name,
			const Namespace & namespaze) :
				Static(location, name, namespaze) {}
		virtual ~Definition() = default;
		std::unique_ptr<ast::Expression> expr;
	};



	struct Global final : public Static {
		Global(
			const SourceLocation & location,
			const std::string & name,
			const Namespace & namespaze) :
				Static(location, name, namespaze) {}
		virtual ~Global() = default;
		std::unique_ptr<ast::Expression> expr;
	private:
	};



	struct Preset final : public Declaration {
		Preset(
			const SourceLocation & location,
			const std::string & name,
			const Namespace & namespaze,
			const std::vector<std::string> & member_names)
			:	Declaration(location, name, namespaze),
				member_names(member_names) {}
		virtual ~Preset() = default;
		std::vector<std::string> member_names;
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