#pragma once
#include "Expression.hxx"

namespace ltn::c::ast {
	struct Literal : public Primary {
		Literal(const lex::DebugInfo & debugInfo) : Primary(debugInfo) {}
		virtual ~Literal() = default;
	};

	struct Integer : public Literal {
	public:
		Integer(std::int64_t value, const lex::DebugInfo & debugInfo)
			:	Literal(debugInfo), value(value) {}
		virtual ~Integer() = default;
		const std::int64_t value;
	};

	struct Float : public Literal {
	public:
		Float(double value, const lex::DebugInfo & debugInfo)
			:	Literal(debugInfo), value(value) {}
		virtual ~Float() = default;
		const double value;
	};

	struct Bool : public Literal {
	public:
		Bool(bool value, const lex::DebugInfo & debugInfo)
			:	Literal(debugInfo), value(value) {}
		virtual ~Bool() = default;
		const bool value;
	};

	struct String : public Literal {
	public:
		String(const std::string & value, const lex::DebugInfo & debugInfo)
			:	Literal(debugInfo), value(value) {}
		virtual ~String() = default;
		const std::string value;
	};

	struct Array : public Literal {
	public:
		Array(const lex::DebugInfo & debugInfo)
			:	Literal(debugInfo) {}
		virtual ~Array() = default;
	};
}