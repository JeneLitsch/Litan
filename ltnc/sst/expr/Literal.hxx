#pragma once
#include <bitset>
#include "stdxx/float64_t.hxx"
#include "Expression.hxx"

namespace ltn::c::sst {
	struct Literal : public Expression {};

	template<typename Derived, typename Value>
	struct LiteralOf : Literal {
		LiteralOf(Value value)
			: Literal()
			, value{std::move(value)} {}

		virtual std::uint64_t alloc() const override {
			return 0;
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			return visitor.visit(static_cast<const Derived &>(*this));
		}

		Value value;
	};



	struct Integer final : public LiteralOf<Integer, std::int64_t> {
		Integer(std::bitset<64> value);
		Integer(std::int64_t value);
	};



	struct Float final : public LiteralOf<Float, stx::float64_t> {
		Float(stx::float64_t value);
	};



	struct Bool final : public LiteralOf<Bool, bool> {
		Bool(bool value) 
			: LiteralOf<Bool, bool>{value} {}
	};



	struct Null final : public LiteralOf<Null, std::nullptr_t> {
		Null() 
			: LiteralOf<Null, std::nullptr_t>{nullptr} {}
	};



	struct Char final : public LiteralOf<Char, std::uint8_t> {
		Char(std::uint8_t value) 
			: LiteralOf<Char, std::uint8_t>{value} {}
	};



	struct String final : public LiteralOf<String, std::string> {
		String(std::string value) 
			: LiteralOf<String, std::string>{std::move(value)} {}
	};
}