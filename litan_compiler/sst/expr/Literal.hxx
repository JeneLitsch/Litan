#pragma once
#include <bitset>
#include "stdxx/float64_t.hxx"
#include "Expression.hxx"

namespace ltn::c::sst::expr {
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
		Integer(std::int64_t value);		
	};



	struct Float final : public LiteralOf<Float, stx::float64_t> {
		Float(stx::float64_t value);
	};



	struct Bool final : public LiteralOf<Bool, bool> {
		Bool(bool value);
	};



	struct Null final : public LiteralOf<Null, std::nullptr_t> {
		Null();
	};





	struct String final : public LiteralOf<String, std::string> {
		String(std::string value); 
	};



	template<typename T>
	concept literal_type = std::is_base_of<sst::expr::Literal, T>::value;



	std::unique_ptr<Integer> integer(std::int64_t value);
	std::unique_ptr<Integer> integer_addr(std::uint64_t value);
	std::unique_ptr<Float> floating(stx::float64_t value);
	std::unique_ptr<Bool> boolean(bool value);
	std::unique_ptr<Null> null();
	std::unique_ptr<String> string(std::string value);
}