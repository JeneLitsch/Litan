#pragma once
#include <functional>
#include "types.hxx"

namespace ltn::c::type {
	struct UnarySignature {
		std::function<bool(const Type & arg)> match;
		std::function<type_ptr()> produce;
	};



	struct BinarySignature {
		std::function<bool(const Type & arg_l, const Type & arg_r)> match;
		std::function<type_ptr()> produce;
	};



	template<typename Result>
	type_ptr produce_result() {
		return std::make_unique<Type>(Result{});
	}



	template<typename Param>
	bool is_valid_unary(const Type & arg) {
		return Param::is_assignable_from(arg);
	}



	template<typename ParamL, typename ParamR>
	bool is_valid_binary_unidirect(const Type & arg_l, const Type & arg_r) {
		return is_valid_unary<ParamL>(arg_l) && is_valid_unary<ParamR>(arg_r);
	}



	template<typename ParamL, typename ParamR>
	bool is_valid_binary_bidirect(const Type & arg_l, const Type & arg_r) {
		constexpr static auto unidirect = is_valid_binary_unidirect<ParamL, ParamR>;
		return unidirect(arg_l, arg_r) && unidirect(arg_r, arg_l);
	}



	template <typename... T>
	struct from {};



	template<typename Param>
	struct from<Param> {
		template<typename Result>
		inline static const UnarySignature to {
			.match = is_valid_unary<Param>,
			.produce = produce_result<Result>,
		};
	};



	template<typename ParamL, typename ParamR>
	struct from<ParamL, ParamR> {
		struct unidirect {
			template<typename Result>
			inline static const BinarySignature to {
				.match = is_valid_binary_unidirect<ParamL, ParamR>,
				.produce = produce_result<Result>,
			};
		};

		struct birect {
			template<typename Result>
			inline static const BinarySignature to {
				.match = is_valid_binary_bidirect<ParamL, ParamR>,
				.produce = produce_result<Result>,
			};
		};
	};
}