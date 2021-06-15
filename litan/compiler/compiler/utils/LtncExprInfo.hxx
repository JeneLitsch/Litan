#pragma once
#include <variant>
#include <string>
#include "LtncType.hxx"
#include "LtncTypeId.hxx"
#include "LtncCodeBuffer.hxx"
namespace ltnc {
	struct Constant {
		Constant(std::int64_t value) : value(value) {}
		Constant(double value) : value(value) {}		
		const std::variant<std::int64_t, double> value;
	};

	struct ExprInfo {

		ExprInfo(const TypeId & typeId, CodeBuffer code)
			: typeId(typeId), code(code)  {}
		
		ExprInfo(const TypeId & typeId, CodeBuffer code, const Constant & constant)
			: typeId(typeId), code(code), constant(constant)  {}

		ExprInfo(const ExprInfo & info) 
			: typeId(info.typeId), code(info.code), constant(info.constant) {}
		
		const TypeId typeId;
		const CodeBuffer code;
		const std::optional<Constant> constant; 
	};
}