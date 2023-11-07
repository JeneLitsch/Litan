#pragma once
#include <vector>
#include <variant>
#include "Expression.hxx"
#include "ltnc/Namespace.hxx"

namespace ltn::c::sst {
	struct Reflect : public ExpressionCRTP<Reflect> {
		struct FunctionQuery {
			std::string id;
			std::string name;
			std::string full_name;
			std::size_t arity;
			bool c0nst; 
			bool pr1vate; 
			bool ext3rn; 
			bool is_variadic; 
		};

		struct NamespaceQuery {
			Namespace namespaze;
			std::vector<FunctionQuery> functions;
		};

		struct LineQuery {
			std::uint64_t line;
		};

		struct FileQuery {
			std::string name;
		};

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

		struct Addr {
			std::uint64_t name;
			std::uint64_t full_name;
			std::uint64_t fx_ptr;
			std::uint64_t functions;
			std::uint64_t c0nst; 
			std::uint64_t pr1vate; 
			std::uint64_t ext3rn; 
			std::uint64_t file; 
			std::uint64_t line; 
			std::uint64_t type; 
		};

		Reflect(Query query, Addr address);
		virtual std::uint64_t alloc() const override;

		Query query;
		Addr address;
	};
}