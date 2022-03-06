#pragma once
#include "Expression.hxx"
#include <bitset>

namespace ltn::c::ast {
	struct Functional;
	struct Var;
	
	struct Literal : public Primary {
		Literal(const SourceLocation & location) : Primary(location) {}
		virtual ~Literal() = default;
	};

	struct Integer : public Literal {
	public:
		Integer(std::bitset<64> value, const SourceLocation & location)
			:	Integer(static_cast<std::int64_t>(value.to_ullong()), location) {}

		Integer(std::int64_t value, const SourceLocation & location)
			:	Literal(location), value(value) {}
		virtual ~Integer() = default;
		std::int64_t value;
	};

	struct Float : public Literal {
	public:
		Float(stx::float64_t value, const SourceLocation & location)
			:	Literal(location), value(value) {}
		virtual ~Float() = default;
		stx::float64_t value;
	};

	struct Bool : public Literal {
	public:
		Bool(bool value, const SourceLocation & location)
			:	Literal(location), value(value) {}
		virtual ~Bool() = default;
		bool value;
	};

	struct Null : public Literal {
	public:
		Null(const SourceLocation & location)
			:	Literal(location) {}
		virtual ~Null() = default;
	};

	struct Char : public Literal {
	public:
		Char(std::uint8_t value, const SourceLocation & location)
			:	Literal(location), value(value) {}
		virtual ~Char() = default;
		std::uint8_t value;
	};

	struct String : public Literal {
	public:
		String(const std::string & value, const SourceLocation & location)
			:	Literal(location), value(value) {}
		virtual ~String() = default;
		std::string value;
	};

	struct Array : public Literal {
	public:
		Array(
			std::vector<std::unique_ptr<Expression>> && initial_elements,
			const SourceLocation & location)
			:	Literal(location),
			initial_elements(std::move(initial_elements)) {}
		virtual ~Array() = default;
		std::vector<std::unique_ptr<Expression>> initial_elements;
	};

	struct Lambda : public Literal {
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