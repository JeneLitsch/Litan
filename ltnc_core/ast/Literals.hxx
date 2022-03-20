#pragma once
#include "Expression.hxx"
#include <bitset>

namespace ltn::c::ast {
	struct Functional;
	struct Var;
	


	struct Enum final : public Primary {
		Enum(std::int64_t value, const SourceLocation & location)
			:	Primary(location), value(value) {}
		virtual ~Enum() = default;
		std::int64_t value;
	};



	struct Literal : public Primary {
		Literal(const SourceLocation & location)
			:	Primary(location) {}
		virtual ~Literal() = default;
	};



	struct Integer final : public Literal {
		Integer(std::bitset<64> value, const SourceLocation & location)
			:	Integer(static_cast<std::int64_t>(value.to_ullong()), location) {}

		Integer(std::int64_t value, const SourceLocation & location)
			:	Literal(location), value(value) {}
		virtual ~Integer() = default;
		std::int64_t value;
	};



	struct Float final : public Literal {
		Float(stx::float64_t value, const SourceLocation & location)
			:	Literal(location), value(value) {}
		virtual ~Float() = default;
		stx::float64_t value;
	};



	struct Bool final : public Literal {
		Bool(bool value, const SourceLocation & location)
			:	Literal(location), value(value) {}
		virtual ~Bool() = default;
		bool value;
	};



	struct Null final : public Literal {
		Null(const SourceLocation & location)
			:	Literal(location) {}
		virtual ~Null() = default;
	};



	struct Char final : public Literal {
		Char(std::uint8_t value, const SourceLocation & location)
			:	Literal(location), value(value) {}
		virtual ~Char() = default;
		std::uint8_t value;
	};



	struct String final : public Literal {
		String(const std::string & value, const SourceLocation & location)
			:	Literal(location), value(value) {}
		virtual ~String() = default;
		std::string value;
	};



	struct Array final: public Literal {
		Array(const SourceLocation & location) : Literal(location) {}
		virtual ~Array() = default;
		std::vector<std::unique_ptr<Expression>> elements;
	};



	struct Lambda final : public Literal {
		Lambda(
			std::unique_ptr<Functional> fx,
			std::vector<std::unique_ptr<Var>> captures,
			const SourceLocation & location)
			:	Literal(location),
				fx(std::move(fx)),
				captures(std::move(captures)) {}
		virtual ~Lambda() = default;
		std::unique_ptr<Functional> fx;
		std::vector<std::unique_ptr<Var>> captures;
	};
}