#pragma once
#include <vector>
#include "stdxx/memory.hxx"
#include "Node.hxx"

namespace ltn::c::ast {
	struct Type : public Node {
		Type(const SourceLocation & source_location) 
		:	Node {source_location} {}
	};

	struct TypeAuto : public Type {
		TypeAuto(const SourceLocation & source_location)
		:	Type {source_location} {}
	};

	struct TypeAny : public Type {
		TypeAny(const SourceLocation & source_location)
		:	Type {source_location} {}
	};

	struct TypeOptional : public Type {
		TypeOptional(
			const SourceLocation & source_location,
			std::unique_ptr<Type> subtype)
		:	Type {source_location}, subtype{std::move(subtype)} {}
		std::unique_ptr<Type> subtype; 
	};

	struct TypeNull : public Type {
		TypeNull(const SourceLocation & source_location)
		:	Type {source_location} {}
	};

	struct TypeBool : public Type {
		TypeBool(const SourceLocation & source_location)
		:	Type {source_location} {}
	};

	struct TypeChar : public Type {
		TypeChar(const SourceLocation & source_location)
		:	Type {source_location} {}
	};

	struct TypeInt : public Type {
		TypeInt(const SourceLocation & source_location)
		:	Type {source_location} {}
	};

	struct TypeFloat : public Type {
		TypeFloat(const SourceLocation & source_location)
		:	Type {source_location} {}
	};

	struct TypeString : public Type {
		TypeString(const SourceLocation & source_location)
		:	Type {source_location} {}
	};

	struct TypeArray : public Type {
		TypeArray(
			const SourceLocation & source_location,
			std::unique_ptr<Type> subtype)
		:	Type {source_location}, subtype{std::move(subtype)} {}
		std::unique_ptr<Type> subtype; 
	};

	struct TypeFxPtr : public Type {
		TypeFxPtr(const SourceLocation & source_location)
		:	Type {source_location} {}
		std::unique_ptr<Type> return_type;
		std::vector<std::unique_ptr<Type>> parameter_types;
	};

	struct TypeQueue : public Type {
		TypeQueue(
			const SourceLocation & source_location,
			std::unique_ptr<Type> subtype)
		: 	Type {source_location}, subtype{std::move(subtype)} {}
		std::unique_ptr<Type> subtype; 
	};

	struct TypeStack : public Type {
		TypeStack(
			const SourceLocation & source_location,
			std::unique_ptr<Type> subtype)
		:	Type {source_location}, subtype{std::move(subtype)} {}
		std::unique_ptr<Type> subtype; 
	};

	struct TypeMap : public Type {
		TypeMap(
			const SourceLocation & source_location,
			std::unique_ptr<Type> keytype,
			std::unique_ptr<Type> valtype)
		:	Type {source_location},
			keytype{std::move(keytype)},
			valtype{std::move(valtype)} {}
		
		std::unique_ptr<Type> keytype; 
		std::unique_ptr<Type> valtype; 
	};

	auto visit_type(const ast::Type & stmt, auto && fx) {
		if(auto s = as<ast::TypeAuto>(stmt)) return fx(*s);
		if(auto s = as<ast::TypeAny>(stmt)) return fx(*s);
		if(auto s = as<ast::TypeOptional>(stmt)) return fx(*s);
		if(auto s = as<ast::TypeNull>(stmt)) return fx(*s);
		if(auto s = as<ast::TypeBool>(stmt)) return fx(*s);
		if(auto s = as<ast::TypeChar>(stmt)) return fx(*s);
		if(auto s = as<ast::TypeInt>(stmt)) return fx(*s);
		if(auto s = as<ast::TypeFloat>(stmt)) return fx(*s);
		if(auto s = as<ast::TypeString>(stmt)) return fx(*s);
		if(auto s = as<ast::TypeArray>(stmt)) return fx(*s);
		if(auto s = as<ast::TypeFxPtr>(stmt)) return fx(*s);
		if(auto s = as<ast::TypeQueue>(stmt)) return fx(*s);
		if(auto s = as<ast::TypeStack>(stmt)) return fx(*s);
		if(auto s = as<ast::TypeMap>(stmt)) return fx(*s);
		throw std::runtime_error{"Unknown statement"};
	}
}
