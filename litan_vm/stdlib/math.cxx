#include "math.hxx"
#include "litan_vm/Exception.hxx"
#include "litan_vm/utils/convert.hxx"
#include "litan_vm/utils/cast.hxx"

namespace ltn::vm::stdlib {
	namespace {
		struct Round {
			inline std::int64_t operator()(const stx::float64_t value) const {
				return static_cast<std::int64_t>(std::round(value));
			}
		};

		struct Floor {
			inline std::int64_t operator()(const stx::float64_t value) const {
				return static_cast<std::int64_t>(std::floor(value));
			}
		};

		struct Ceil {
			inline std::int64_t operator()(const stx::float64_t value) const {
				return static_cast<std::int64_t>(std::ceil(value));
			}
		};

		struct Absolute {
			template <typename T>
			inline auto operator()(const T value) const {
				using Promoted = decltype(value + std::int64_t(1));
				if constexpr(std::is_unsigned_v<T>) {
					return static_cast<Promoted>(value);
				}
				else {
					return static_cast<Promoted>(std::abs(value));
				}
			}
		};

		struct Sinus {
			inline stx::float64_t operator()(const auto value) const {
				return std::sin(static_cast<stx::float64_t>(value));
			}
		};

		struct Cosinus {
			inline stx::float64_t operator()(const auto value) const {
				return std::cos(static_cast<stx::float64_t>(value));
			}
		};

		struct Tangents {
			inline stx::float64_t operator()(const auto value) const {
				return std::tan(static_cast<stx::float64_t>(value));
			}
		};
	}

	template<class Fx>
	Value rounding(const Value & value) {
		constexpr Fx fx{};
		if(is_float(value)) {
			return value::deduce(fx(value.f));
		}
		if(is_int(value) || is_bool(value)) {
			return value::integer(cast::to_int(value));
		}
		throw except::invalid_argument();
	}



	template<class Fx>
	Value function(const Value & value) {
		constexpr Fx fx{};
		if(is_float(value)) {
			return value::deduce(fx(value.f));
		}
		if(is_int(value)) {
			return value::deduce(fx(value.i));
		}
		if(is_bool(value)) {
			return value::deduce(fx(value.b));
		}
		throw except::invalid_argument();
	}



	Value min::func(Context * context, const Value * args) {
		VMCore & core = *static_cast<VMCore*>(context->core);
		const Value a = args[1];
		const Value b = args[0];
		return compare(a, b, core) <= 0 ? a : b;
	}



	Value max::func(Context * context, const Value * args) {
		VMCore & core = *static_cast<VMCore*>(context->core);
		const Value a = args[1];
		const Value b = args[0];
		return compare(a, b, core) >= 0 ? a : b;
	}



	Value clamp::func(Context * context, const Value * args) {
		VMCore & core = *static_cast<VMCore*>(context->core);
		const Value max = args[2];
		const Value min = args[1];
		const Value val = args[0];

		if(compare(val, min, core) < 0) {
			return min;
		}

		if(compare(val, max, core) > 0) {
			return max;
		}

		return val;
	}



	Value round::func(Context * context, const Value * args) {
		return rounding<Round>(args[0]);
	}



	Value floor::func(Context * context, const Value * args) {
		return rounding<Floor>(args[0]);
	}



	Value ceil::func(Context * context, const Value * args) {
		return rounding<Ceil>(args[0]);
	}



	Value abs::func(Context * context, const Value * args) {
		return function<Absolute>(args[0]);
	}



	Value sin::func(Context * context, const Value * args) {
		return function<Sinus>(args[0]);
	}



	Value cos::func(Context * context, const Value * args) {
		return function<Cosinus>(args[0]);
	}



	Value tan::func(Context * context, const Value * args) {
		return function<Tangents>(args[0]);
	}



	Value sqrt::func(Context * context, const Value * args) {
		const auto value = args[0];
		return value::floating(std::sqrt(convert::to_float(value)));
	}
	


	Value hypot::func(Context * context, const Value * args) {
		const auto r = args[1];
		const auto l = args[0];
		return value::floating(
			std::hypot(
				convert::to_float(l),
				convert::to_float(r)
			)
		);
	}



	Value log::func(Context * context, const Value * args) {
		const auto r = args[1];
		const auto l = args[0];
		return value::floating(
			std::log(convert::to_float(l))	/ std::log(convert::to_float(r))
		);
	}
	

	
	Value ln::func(Context * context, const Value * args) {
		const auto value = args[0];
		return value::floating(std::log(convert::to_float(value)));
	}



	Value ld::func(Context * context, const Value * args) {
		return value::floating(std::log(convert::to_float(args[0])) / std::log(2.0));
	}



	Value lg::func(Context * context, const Value * args) {
		return value::floating(std::log(convert::to_float(args[0])) / std::log(10.0));
	}
}