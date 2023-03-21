#pragma once

namespace ltn::c {
	enum class UnaryOp { NEG, NOT, NUL, BITNOT, DEREF };



	enum class TypedUnaryOp {
		CONVERSION,
		STATIC_CAST, DYNAMIC_CAST, FORCE_CAST,
		STATIC_COPY, DYNAMIC_COPY, FORCE_COPY,
	};



	enum class BinaryOp {
		ADD, SUB,
		MLT, DIV, MOD, POW,
		BIGGER, SMALLER, BIGGEREQUAL, SMALLEREQUAL,
		EQUAL, UNEQUEL,
		SPACE_SHIP,
		SHIFT_L, SHIFT_R,
		AND, OR,
		NULLCO, ELVIS,
		BIT_OR, BIT_AND, BIT_XOR,
	};
}