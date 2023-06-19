#include "instructions.hxx"
#include "stdxx/string.hxx"
#include "stdxx/array.hxx"
#include <cmath>
#include "ltnvm/utils/type_check.hxx"
#include <sstream>
#include "ltnvm/utils/calc_binary.hxx"
#include "ltnvm/utils/convert.hxx"
#include "ltnvm/utils/cast.hxx"
#include "ltnvm/utils/special_member.hxx"

#define LTNVM_BINRY_FETCH\
	const auto r = core.stack.pop();\
	auto & l = core.stack.peek_ref();


namespace ltn::vm::inst {
	namespace {
		template<typename T>
		inline std::uint64_t concat(const Value & l, const Value & r, Heap & heap) {
			const auto obj_l = heap.read<T>(l.u);
			const auto obj_r = heap.read<T>(r.u);
			return heap.alloc<T>({obj_l + obj_r});
		} 



		template<typename Container>
		std::uint64_t repeat(
			const Value & ref,
			const Value & repetitions,
			Heap & heap) {
			
			const auto & str = heap.read<Container>(ref.u);
			const auto & count = cast::to_int(repetitions);
			auto repeated = stx::repeat(str, count);
			const auto ptr = heap.alloc<Container>(std::move(repeated)); 
			return ptr;
		}


				// Promotes operands to at least int64
		// Bool --> Int -?> Double
		template<class Op>
		struct Promoted {
			constexpr inline auto operator()(const auto l, const auto r) const {
				constexpr Op op{};
				using T = decltype(l+r+std::int64_t(1));
				return op(static_cast<T>(l), static_cast<T>(r));
			}
		};

		using Addition = Promoted<std::plus<void>>;
		using Subtraction = Promoted<std::minus<void>>;
		using Multiplication = Promoted<std::multiplies<void>>;



		auto add(auto a, auto b) {
			return a + b;
		}


		auto sub(auto a, auto b) {
			return a - b;
		}


		auto mlt(auto a, auto b) {
			return a * b;
		}


		auto div(auto a, auto b) {
			return a / b;
		}


		auto mod(std::integral auto a, std::integral auto b) {
			return a % b;
		}


		auto mod(std::floating_point auto a, std::floating_point auto b) {
			return std::fmod(a, b);
		}


		struct Division {
			constexpr auto operator()(const auto l, const auto r) const {
				if(r == 0) throw except::division_by_zero();
				using T = decltype(l+r+std::int64_t(1));
				return static_cast<T>(l) / static_cast<T>(r);
			}
		};

		
		
		struct Modulo {
			constexpr auto operator()(const auto l, const auto r) const {
				if(r == 0) throw except::division_by_zero();
				using T = decltype(l+r+std::int64_t(1));
				if constexpr(std::integral<T>) {
					return static_cast<std::int64_t>(l%r);
				}
				else {
					return std::fmod(l, r);
				}
			}
		};



		struct Power {
			constexpr auto operator()(const auto l, const auto r) const 
				-> decltype(l+r+std::int64_t(1)) {
				
				using T = decltype(l+r+std::int64_t(1));
				return static_cast<T>(std::pow(static_cast<T>(l), static_cast<T>(r)));
			}
		};
	}



	#define LTNVM_BINARY_ARITH(OP)\
	case Value::Type::BOOL: switch (r.type) {\
		case Value::Type::BOOL:  l = value::integer(OP(l.b, r.b)); return;\
		case Value::Type::CHAR:  l = value::integer(OP(l.b, r.c)); return;\
		case Value::Type::INT:   l = value::integer(OP(l.b, r.i)); return;\
		case Value::Type::FLOAT: l = value::floating(OP(l.b, r.f)); return;\
	} break;\
	\
	case Value::Type::CHAR: switch (r.type) {\
		case Value::Type::BOOL:  l = value::integer(OP(l.c, r.b)); return;\
		case Value::Type::CHAR:  l = value::integer(OP(l.c, r.c)); return;\
		case Value::Type::INT:   l = value::integer(OP(l.c, r.i)); return;\
		case Value::Type::FLOAT: l = value::floating(OP(l.c, r.f)); return;\
	} break;\
	\
	case Value::Type::INT: switch (r.type) {\
		case Value::Type::BOOL:  l = value::integer(OP(l.i, r.b)); return;\
		case Value::Type::CHAR:  l = value::integer(OP(l.i, r.c)); return;\
		case Value::Type::INT:   l = value::integer(OP(l.i, r.i)); return;\
		case Value::Type::FLOAT: l = value::floating(OP(l.i, r.f)); return;\
	} break;\
	\
	case Value::Type::FLOAT: switch (r.type) {\
		case Value::Type::BOOL:   l = value::floating(OP(l.f, r.b)); return;\
		case Value::Type::CHAR:   l = value::floating(OP(l.f, r.c)); return;\
		case Value::Type::INT:    l = value::floating(OP(l.f, r.i)); return;\
		case Value::Type::FLOAT:  l = value::floating(OP(l.f, r.f)); return;\
	} break;



	#define LTNVM_BINARY_MEMBER(CODE)\
	case Value::Type::STRUCT: l = call_special_member<MemberCode::CODE>(core, l, r); return;



	#define LTNVM_BINARY_CONCAT(RESULT, TYPECODE, DATATYPE)\
	case Value::Type::TYPECODE: switch (r.type) {\
		case Value::Type::TYPECODE:\
			l = value::RESULT(concat<DATATYPE>(l,r,core.heap));\
			return;\
	} break;



	void add(VmCore & core) {
		LTNVM_BINRY_FETCH

		switch (l.type) {
			LTNVM_BINARY_ARITH(add)
			LTNVM_BINARY_MEMBER(ADD)
			LTNVM_BINARY_CONCAT(string, STRING, String)
			LTNVM_BINARY_CONCAT(array, ARRAY, Array)
			LTNVM_BINARY_CONCAT(tuple, TUPLE, Array)
		}

		throw except::invalid_operands();
	}



	void sub(VmCore & core) {
		LTNVM_BINRY_FETCH

		switch (l.type) {
			LTNVM_BINARY_ARITH(sub)
			LTNVM_BINARY_MEMBER(SUB)
		}

		throw except::invalid_operands();
	}



	void mlt(VmCore & core) {
		LTNVM_BINRY_FETCH

		if(is_string(l) && is_integral(r)) {
			l = value::string(repeat<String>(l, r, core.heap));
			return;
		}

		if(is_integral(l) && is_string(r)) {
			l = value::string(repeat<String>(r, l, core.heap));
			return;
		}

		if(is_array(l) && is_integral(r)) {
			l = value::array(repeat<Array>(l, r, core.heap));
			return;
		}

		if(is_integral(l) && is_array(r)) {
			l = value::array(repeat<Array>(r, l, core.heap));
			return;
		}

		if(is_struct(l)) {
			l = call_special_member<MemberCode::MLT>(core, l, r);
			return;
		}

		l = calc<Multiplication>(l, r);
	}



	void div(VmCore & core) {
		LTNVM_BINRY_FETCH

		if(is_struct(l)) {
			l = call_special_member<MemberCode::DIV>(core, l, r);
			return;
		}

		l = calc<Division>(l, r);
	}



	void mod(VmCore & core) {
		LTNVM_BINRY_FETCH

		if(is_struct(l)) {
			l = call_special_member<MemberCode::MOD>(core, l, r);
			return;
		}

		l = calc<Modulo>(l, r);
	}



	void pow(VmCore & core) {
		LTNVM_BINRY_FETCH

		if(is_struct(l)) {
			l = call_special_member<MemberCode::POW>(core, l, r);
			return;
		}

		l = calc<Power>(l, r);
	}
}
#undef LTNVM_BINRY_FETCH
#undef LTNVM_BINRY_ARITH
#undef LTNVM_BINRY_MEMBER
#undef LTNVM_BINRY_CONCAT