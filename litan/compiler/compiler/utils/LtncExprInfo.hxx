#pragma once
#include <variant>
#include <string>
#include "LtncType.hxx"
#include "LtncTypeId.hxx"
#include "LtncCodeBuffer.hxx"
#include "LtncConstValue.hxx"
namespace ltnc {
	struct ExprInfo {

		ExprInfo(
			const TypeId & typeId,
			CodeBuffer code)
		:	typeId(typeId),
			code(code) {}
		
		ExprInfo(
			const TypeId & typeId,
			CodeBuffer code,
			const ConstValue & constValue)
		: 	typeId(typeId),
			code(code),
			constValue(constValue) {}

		ExprInfo(
			const ExprInfo & info) 
		: 	typeId(info.typeId),
			code(info.code),
			constValue(info.constValue){}
		
		const TypeId typeId;
		const CodeBuffer code;
		const std::optional<ConstValue> constValue; 
	};
}