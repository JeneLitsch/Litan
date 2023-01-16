#include "instantiate_type.hxx"
#include "stdxx/functional.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/type/traits.hxx"

namespace ltn::c {
	type::Type instantiate_type(
		const type::Type & incomplete,
		const Scope & scope);


	type::Any instantiate(
		const type::Any &,
		const Scope &) {
		return type::Any{};
	}



	type::Type instantiate(
		const type::Other & incomplete,
		const Scope & scope) {
		auto * type = scope.resolve_type(incomplete.type_name);
		if(type) return *type;
		throw CompilerError{
			"Undeclared type " + incomplete.type_name 
		};
	}



	type::Optional instantiate(
		const type::Optional & incomplete,
		const Scope & scope) {
		const auto & inner = incomplete.contains;
		if(is_optional(inner)) return type::Optional {
			.contains = instantiate_type(inner.as<type::Optional>()->contains, scope)
		};
		return type::Optional{
			.contains = instantiate_type(inner, scope)
		};
	}



	type::Error instantiate(
		const type::Error &,
		const Scope &) {
		return type::Error{};
	}



	type::Null instantiate(
		const type::Null &,
		const Scope &) {
		return type::Null{};
	}



	type::Bool instantiate(
		const type::Bool &,
		const Scope &) {
		return type::Bool{};
	}



	type::Char instantiate(
		const type::Char &,
		const Scope &) {
		return type::Char{};
	}



	type::Int instantiate(
		const type::Int &,
		const Scope &) {
		return type::Int{};
	}



	type::Float instantiate(
		const type::Float &,
		const Scope &) {
		return type::Float{};
	}



	type::String instantiate(
		const type::String &,
		const Scope &) {
		return type::String{};
	}



	type::Array instantiate(
		const type::Array & incomplete,
		const Scope & scope) {
		return type::Array{
			.contains = instantiate_type(*incomplete.contains, scope)
		};
	}



	type::Tuple instantiate(
		const type::Tuple & incomplete,
		const Scope & scope) {
		std::vector<type::Type> contained;
		for(const auto & elem : incomplete.contained) {
			contained.push_back(instantiate_type(elem, scope));
		}
		return type::Tuple{
			.contained = std::move(contained),
		};
	}



	type::FxPtr instantiate(
		const type::FxPtr & incomplete,
		const Scope & scope) {
		std::vector<type::Type> parameters;
		for(const auto & parameter : incomplete.parameter_types) {
			parameters.push_back(instantiate_type(parameter, scope));
		}
		return type::FxPtr{
			.return_type = instantiate_type(incomplete.return_type, scope),
			.parameter_types = std::move(parameters),
		};
	}



	type::Queue instantiate(
		const type::Queue & incomplete,
		const Scope & scope) {
		return type::Queue{
			.contains = instantiate_type(incomplete.contains, scope)
		};
	}



	type::Stack instantiate(
		const type::Stack & incomplete,
		const Scope & scope) {
		return type::Stack{
			.contains = instantiate_type(incomplete.contains, scope)
		};
	}



	type::Map instantiate(
		const type::Map & incomplete,
		const Scope & scope) {
		return type::Map{
			.key = instantiate_type(incomplete.key, scope),
			.val = instantiate_type(incomplete.val, scope),
		};
	}



	type::Istream instantiate(
		const type::Istream &,
		const Scope &) {
		return type::Istream{};
	}



	type::Ostream instantiate(
		const type::Ostream &,
		const Scope &) {
		return type::Ostream{};
	}



	type::Type instantiate_type(
		const type::Type & type,
		const Scope & scope) {
		return type::visit(type, [&] (auto & t) -> type::Type {
			return instantiate(t, scope);
		});
	}



	type::Type instantiate_type(
		const type::IncompleteType & incomplete,
		const Scope & scope) {
		return instantiate_type(incomplete.type, scope);
	}
}