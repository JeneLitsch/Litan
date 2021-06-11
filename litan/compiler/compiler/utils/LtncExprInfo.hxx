#pragma once
#include <variant>
#include <string>
#include "LtncType.hxx"
namespace ltnc {
	struct Constant {
		Constant(std::int64_t value) : value(value) {}
		Constant(double value) : value(value) {}		
		const std::variant<std::int64_t, double> value;
	};

	struct ExprInfo {

		ExprInfo(Type type, std::string code)
			: type(type), code(code)  {}
		
		ExprInfo(Type type, std::string code, const Constant & constant)
			: type(type), code(code), constant(constant)  {}

		ExprInfo(const ExprInfo & info) 
			: type(info.type), code(info.code), constant(info.constant) {}
		
		const Type type;
		const std::string code;
		const std::optional<Constant> constant; 
	};
}