#pragma once

#include <tuple>
#include <vector>
#include <sstream>
#include <optional>
#include "litan_core/unique.hxx"
#include "litan_compiler/Namespace.hxx"
#include "litan_compiler/Qualifiers.hxx"
#include "litan_compiler/ast/decl/Declaration.hxx"

namespace ltn::c::ast::decl {
	struct Parameter {
		std::string name;
	};

	struct Parameters {
		std::vector<Parameter> simple;
		std::optional<Parameter> variadic;
	};



	struct Except final : public Node {
		Except(
			const std::string & errorname,
			stmt_ptr && body,
			const SourceLocation & location);
		virtual ~Except();
		stmt_ptr body;
		std::string errorname;
	};



	struct Function : public Declaration {
		Function(
			const std::string & name,
			Namespace namespaze,
			Parameters parameters,
			stmt_ptr body,
			const SourceLocation & location);

		virtual ~Function();

		Parameters parameters;
		Qualifiers qualifiers; 
		stmt_ptr body;
		std::unique_ptr<Except> except;
		
		const std::string & get_resolve_name() const {
			return this->name;
		}

		const Namespace & get_resolve_namespace() const {
			return this->namespaze;
		}
	};
}