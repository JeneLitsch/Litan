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
			code(code),
			assignable(false)  {}
		
		ExprInfo(
			const TypeId & typeId,
			CodeBuffer code,
			const ConstValue & constValue)
		: 	typeId(typeId),
			code(code),
			constValue(constValue),
			assignable(false)  {}

		ExprInfo(
			const TypeId & typeId,
			CodeBuffer code,
			const ConstValue & constValue,
			bool assignable)
		: 	typeId(typeId),
			code(code),
			constValue(constValue),
			assignable(assignable)  {}

		ExprInfo(
			const TypeId & typeId,
			CodeBuffer code,
			bool assignable)
		:	typeId(typeId),
			code(code),
			assignable(assignable)  {}

		ExprInfo(
			const ExprInfo & info) 
		: 	typeId(info.typeId),
			code(info.code),
			constValue(info.constValue),
			assignable(false) {}
		
		const TypeId typeId;
		const CodeBuffer code;
		const std::optional<ConstValue> constValue; 
		const bool assignable;
	};
}