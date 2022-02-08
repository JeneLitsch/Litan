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
		Float(double value, const SourceLocation & location)
			:	Literal(location), value(value) {}
		virtual ~Float() = default;
		double value;
	};

	struct Bool : public Literal {
	public:
		Bool(bool value, const SourceLocation & location)
			:	Literal(location), value(value) {}
		virtual ~Bool() = default;
		bool value;
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
			std::vector<std::unique_ptr<Expression>> && initElements,
			const SourceLocation & location)
			:	Literal(location),
			initElements(std::move(initElements)) {}
		virtual ~Array() = default;
		std::vector<std::unique_ptr<Expression>> initElements;
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