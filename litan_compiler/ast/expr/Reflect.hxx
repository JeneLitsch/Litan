#pragma once
#include "Expression.hxx"

namespace ltn::c::ast::expr {
	struct Reflect final : public Expression {
		struct NamespaceQuery {
			Namespace namespaze;
		};
		
		struct FunctionQuery {
			Namespace namespaze;
			std::string name;
			std::size_t arity;
			bool is_variadic;
		};
		
		struct FileQuery {};
		
		struct LineQuery {};
		
		struct LocationQuery {
			FileQuery file;
			LineQuery line;
		};
		
		using Query = std::variant<
			NamespaceQuery,
			FunctionQuery,
			FileQuery,
			LineQuery,
			LocationQuery
		>;
		
		Reflect(Query query, const SourceLocation & location);
		virtual void accept(const ExprVisitor & visitor) const override;

		Query query;
	};

	std::unique_ptr<Reflect> reflect(const SourceLocation & location, Reflect::Query query);
}