#include "LtncCompilerFunctions.hxx"

// (a) ? (b) : (c)
ltn::c::ExprInfo ltn::c::compile::ternary(
	CompilerPack & compPkg,
	const ExprTernary & expr) {
	

	// Compile Expressions
	const ExprInfo exprCondition = expression(compPkg, *expr.condition);
	const ExprInfo exprTrue = expression(compPkg, *expr.trueBranch);
	const ExprInfo exprFalse = expression(compPkg, *expr.falseBranch);


	// Create jumpmarks
	SymbolTable & sTable = compPkg.getSymbolTable();
	const auto jumpTrue = sTable.makeJumpMark("TERNARY_TRUE_");
	const auto jumpFalse = sTable.makeJumpMark("TERNARY_FALSE_");
	const auto jumpEnd = sTable.makeJumpMark("TERNARY_END_");



	// Check types
	const bool conditionTypeValid =
		(exprCondition.typeId == TypeId(TBool)) ||
		(exprCondition.typeId == TypeId(TInt));
	
	if(!conditionTypeValid) {
		throw ltn::c::error::incompatibleTypes(
			expr.debugInfo,	exprCondition.typeId, TypeId(TBool));
	}

	const bool branchTypesEqual =
		exprTrue.typeId == exprFalse.typeId;
	
	if(!branchTypesEqual) {
		throw ltn::c::error::incompatibleTypes(
			expr.debugInfo,	exprTrue.typeId, exprFalse.typeId);
	}



	// Generate code
	CodeBuffer code = compPkg.codeBuffer();
	// condition
	code 
		<< exprCondition.code
		<< AssemblyCode("ifnx")
		<< Inst::got0(jumpTrue)
		<< Inst::got0(jumpFalse);
	
	// expr true
	code 
		<< Inst::mark(jumpTrue)
		<< exprTrue.code
		<< Inst::got0(jumpEnd);
	
	// expr false
	code 
		<< Inst::mark(jumpFalse)
		<< exprFalse.code
		<< Inst::got0(jumpEnd);

	code
		<< Inst::mark(jumpEnd);


	return ExprInfo(exprTrue.typeId, code);
}
