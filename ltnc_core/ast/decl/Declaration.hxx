#pragma once
#include "../Node.hxx"
#include "../Namespace.hxx"
#include <map>

namespace ltn::c::ast {
	struct Expression;



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



	struct Global final : public Declaration {
		Global(
			const SourceLocation & location,
			const std::string & name,
			const Namespace & namespaze)
			:	Declaration(location, name, namespaze) {}
		virtual ~Global() = default;
		std::unique_ptr<ast::Expression> expr;
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
}