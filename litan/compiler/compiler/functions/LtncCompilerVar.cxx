#include "LtncCompilerFunctions.hxx"
#include <functional>


ltn::c::Var resolveVariable(
	const ltn::c::ExprVar & expr,
	const ltn::c::SymbolTable & sTable) {

	const auto & path = expr.path;
	try {
		return sTable.match(expr.debugInfo, ltn::c::VarId(path[0])); 
	}
	catch(...) {
		throw ltn::c::error::undefinedVariable(path[0], expr.debugInfo);
	}
}


ltn::c::Var resolveMember(
	const unsigned i,
	const ltn::c::ExprVar & expr,
	const ltn::c::SymbolTable & sTable,
	const ltn::c::Var & lastVar) {

	const auto & path = expr.path;

	// lookup struct type
	const ltn::c::Type & type = sTable.match(expr.debugInfo, lastVar.typeId);
	// search next member
	const auto & members = type.members; 
	for(const auto & newVar : members) {
		if(newVar->name == path[i]) {
			return *newVar;
		}
	}
	// undefined member
	throw ltn::c::error::notAMember(path[i], type.id, expr.debugInfo);
}


ltn::c::Var resolveNext(
	const unsigned i,
	const ltn::c::SymbolTable & sTable,
	const ltn::c::Var & lastVar,
	const ltn::c::ExprVar & expr) {
	
	const bool isFirst = (i == 0);

	if(isFirst) {
		return resolveVariable(expr, sTable);
	}
	else {
		return resolveMember(i, expr, sTable, lastVar);
	}
}



ltn::c::CodeBuffer readStack(const ltn::c::Var & var){
	ltn::c::CodeBuffer code(false);
	code << ltn::c::Inst::load(var.addr);
	return code;
}



ltn::c::CodeBuffer readHeap(const ltn::c::Var & var) {
	ltn::c::CodeBuffer code(false);
	code << ltn::c::Inst::newl(var.addr);
	code << ltn::c::AssemblyCode("array::get");
	return code;
}


ltn::c::CodeBuffer read(
	const bool isStack,
	const ltn::c::Var & var) {
	if(isStack) {
		return readStack(var);
	}
	else {
		return readHeap(var);
	}
}


ltn::c::CodeBuffer writeStack(
	const ltn::c::Var & var,
	const ltn::c::ExprInfo & exprInfo) {
	
	ltn::c::CodeBuffer code(false);
	code << exprInfo.code;
	code << ltn::c::Inst::store(var.addr);
	return code;
}



ltn::c::CodeBuffer writeHeap(
	const ltn::c::Var & var,
	const ltn::c::ExprInfo & exprInfo) {
	
	ltn::c::CodeBuffer code(false);
	code << ltn::c::Inst::newl(var.addr);
	code << exprInfo.code;
	code << ltn::c::AssemblyCode("array::set");
	return code;
}


ltn::c::CodeBuffer write(
	const bool isStack,
	const ltn::c::Var & var,
	const ltn::c::ExprInfo & exprInfo) {

	if(isStack) {
		return writeStack(var, exprInfo);
	}
	else {
		return writeHeap(var, exprInfo);
	}
}


ltn::c::CodeBuffer generateCode(
	const bool isStack,
	const bool isLast,
	const ltn::c::Var & var,
	const std::optional<ltn::c::ExprInfo> & exprInfo) {

	const bool isWrite = exprInfo && isLast;

	if(isWrite) {
		return write(isStack, var, *exprInfo);
	}
	else {
		return read(isStack, var);
	}
}


ltn::c::ExprInfo ltn::c::compile::var(CompilerPack & compPkg, const ExprVar & varExpr, const std::optional<ExprInfo> & exprInfo) {

	CodeBuffer code = compPkg.codeBuffer();
	Var var(TypeId(""), 0, VarId(""));


	// follow refs
	for(unsigned i = 0; i < varExpr.path.size(); i++) {
		const SymbolTable & sTable = compPkg.getSymbolTable(); 
		const std::size_t pathEnd = varExpr.path.size() - 1;
		const bool isFirst = (i == 0);
		const bool isLast = (i == pathEnd);

		var = resolveNext(i, sTable, var, varExpr);
		code << generateCode(isFirst, isLast, var, exprInfo);
	}


	return ExprInfo(var.typeId, code);
}
