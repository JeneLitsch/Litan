#include "Literal.hxx"

namespace ltn::c::sst::expr {
	Float::Float(stx::float64_t value)   : LiteralOf<Float, stx::float64_t>{value} {}
	Integer::Integer(std::int64_t value) : LiteralOf<Integer, std::int64_t>{value} {}
	Bool::Bool(bool value)               : LiteralOf<Bool, bool>{value} {}
	Null::Null()                         : LiteralOf<Null, std::nullptr_t>{nullptr} {}
	Char::Char(std::uint8_t value)       : LiteralOf<Char, std::uint8_t>{value} {}
	String::String(std::string value)    : LiteralOf<String, std::string>{std::move(value)} {}



	std::unique_ptr<Integer> integer(std::int64_t value) {
		return std::make_unique<Integer>(value);
	}

	std::unique_ptr<Integer> integer_addr(std::uint64_t value) {
		return integer(static_cast<std::int64_t>(value));
	}

	std::unique_ptr<Float> floating(stx::float64_t value) {
		return std::make_unique<Float>(value);
	}

	std::unique_ptr<Bool> boolean(bool value) {
		return std::make_unique<Bool>(value);
	}

	std::unique_ptr<Null> null() {
		return std::make_unique<Null>();
	}

	std::unique_ptr<Char> character(std::uint8_t value) {
		return std::make_unique<Char>(value);
	}

	std::unique_ptr<String> string(std::string value) {
		return std::make_unique<String>(std::move(value));
	}

}