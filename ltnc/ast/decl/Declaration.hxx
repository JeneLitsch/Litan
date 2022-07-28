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



	struct Definition final : public Declaration {
		Definition(
			const SourceLocation & location,
			const std::string & name,
			const Namespace & namespaze)
			:	Declaration(location, name, namespaze) {}
		virtual ~Definition() = default;
		std::unique_ptr<ast::Expression> expr;
	};



	struct Global final : public Declaration {
		Global(
			const SourceLocation & location,
			const std::string & name,
			const Namespace & namespaze) :
				Declaration(location, name, namespaze),
				id(++counter) {}
		virtual ~Global() = default;
		std::uint64_t id;
	private:
		static inline std::uint64_t counter = 0;
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