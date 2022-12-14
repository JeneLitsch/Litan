#pragma once

#include <tuple>
#include <vector>
#include <sstream>
#include "ltn/unique.hxx"
#include "Declaration.hxx"
#include "ltnc/Namespace.hxx"
#include "ltnc/type/Type.hxx"

namespace ltn::c::sst {
	struct Statement;
	struct Statement;
	struct Parameter {
		std::string name;
		type::Type type = type::Type{type::Any{}};
	};
	using Parameters = std::vector<Parameter>;



	inline std::string mangle(
		const std::string & name,
		const Namespace & namespaze,
		const Parameters & parameters) {
		std::ostringstream oss;
		oss << namespaze.to_string();
		oss << name << "(";
		oss << std::size(parameters) << ")";
		return oss.str();
	}



	struct Except final : public Node {
		Except(
			const std::string & errorname,
			std::unique_ptr<Statement> && body)
			:	body(std::move(body)),
				errorname(errorname) {}
		virtual ~Except() = default;
		std::unique_ptr<Statement> body;
		std::string errorname;
	};



	struct Functional : public Declaration {
		Functional(
			const std::string & id,
			const std::string & name,
			Namespace namespaze,
			Parameters parameters,
			const type::Type & return_type)
			:	Declaration(name, namespaze),
				parameters(parameters),
				id(id),
				return_type{return_type} {}
		virtual ~Functional() = default;

		Parameters parameters;
		bool c0nst = false;
		bool pr1vate = false;
		bool init = false;

		std::string id;
		type::Type return_type;

		const std::string & get_resolve_name() const {
			return this->name;
		}

		const Namespace & get_resolve_namespace() const {
			return this->namespaze;
		}
	};


	struct Var;
	struct Function final : public Functional {
		Function(
			const std::string & id,
			const std::string & name,
			Namespace namespaze,
			Parameters parameters,
			std::unique_ptr<Statement> && body,
			const type::Type & return_type)
			:	Functional{id, name, namespaze, parameters, return_type},
				body(std::move(body)) {}

		Function(
			const std::string & id,
			const std::string & name,
			Namespace namespaze,
			Parameters parameters,
			std::unique_ptr<Statement> && body)
			:	Functional{id, name, namespaze, parameters, type::Any{}},
				body(std::move(body)) {}
		virtual ~Function() = default;
		std::unique_ptr<Statement> body;
		std::unique_ptr<Except> except;
		std::vector<std::unique_ptr<Var>> capture;
	};



	struct FunctionTemplate : public Node {
		FunctionTemplate(
			std::unique_ptr<Functional> fx,
			std::vector<std::string> template_parameters)
			:	fx{std::move(fx)},
				template_parameters{std::move(template_parameters)} {}
		virtual ~FunctionTemplate() = default;
		
		std::unique_ptr<Functional> fx;
		std::vector<std::string> template_parameters;

		const std::string & get_resolve_name() const {
			return this->fx->get_resolve_name();
		}

		const Namespace & get_resolve_namespace() const {
			return this->fx->get_resolve_namespace();
		}
	};



	struct BuildIn final : public Functional {
		BuildIn(
			const std::string & id,
			const std::string & name,
			Namespace namespaze,
			Parameters parameters,
			const std::string & key,
			const type::Type & return_type)
			:	Functional{id, name, namespaze, parameters, return_type},
				key(key) {}
		virtual ~BuildIn() = default;
		std::string key;		
	};
}