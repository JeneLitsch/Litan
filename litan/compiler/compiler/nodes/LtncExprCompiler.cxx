#include "LtncExprCompiler.hxx"
#include "LtncVariCompiler.hxx"

#include "LtncAddEvaluator.hxx"
#include "LtncSubEvaluator.hxx"
#include "LtncMltEvaluator.hxx"
#include "LtncDivEvaluator.hxx"
#include "LtncModEvaluator.hxx"

#include "LtncInst.hxx"

#include "Unused.hxx"
#include <iostream>
#include <sstream>
#include <functional>
#include "LtncBaseTypes.hxx"


ltnc::ExprCompiler::ExprCompiler(
	const VariCompiler & variCompiler) 
	: variCompiler(variCompiler) {}


ltnc::ExprInfo ltnc::ExprCompiler::compile(CompilerPack & compPkg, const std::shared_ptr<Expr> & expr) const {
	return this->compileExpr(compPkg, expr);
}


ltnc::ExprInfo ltnc::ExprCompiler::compileExpr(CompilerPack & compPkg,  std::shared_ptr<Expr> expr) const {
	if(auto expr_ = std::dynamic_pointer_cast<ltnc::ExprIntLiteral>(expr)) {
		return this->compileIntLit(compPkg, expr_);
	}
	if(auto expr_ = std::dynamic_pointer_cast<ltnc::ExprFltLiteral>(expr)) {
		return this->compileFltLit(compPkg, expr_);
	}
	if(auto expr_ = std::dynamic_pointer_cast<ltnc::ExprStrLiteral>(expr)) {
		return this->compileStrLit(compPkg, expr_);
	}
	if(auto expr_ = std::dynamic_pointer_cast<ltnc::ExprVar>(expr)) {
		return this->variCompiler.compile(compPkg, expr_, {});
	}
	if(auto expr_ = std::dynamic_pointer_cast<ltnc::ExprBinary>(expr)) {
		return this->compileBinary(compPkg, expr_);
	}
	if(auto expr_ = std::dynamic_pointer_cast<ltnc::ExprCall>(expr)) {
		return this->compileCall(compPkg, expr_);
	}
	if(auto expr_ = std::dynamic_pointer_cast<ltnc::ExprUnary>(expr)) {
		return this->compileUnary(compPkg, expr_);
	}
	throw std::runtime_error("Invalid Expr");
}


ltnc::ExprInfo ltnc::ExprCompiler::compileBinary(CompilerPack & compPkg, std::shared_ptr<ExprBinary> expr) const {
	static const AddEvaluator addEvaluator;
	static const SubEvaluator subEvaluator;
	static const MltEvaluator mltEvaluator;
	static const DivEvaluator divEvaluator;
	static const ModEvaluator modEvaluator;
	
	switch (expr->type)	{
	// comparision operator
	case TokenType::EQUAL:			return this->buildBinary(compPkg, expr, "eql");
	case TokenType::UNEQUAL: 		return this->buildBinary(compPkg, expr, "uneql");
	case TokenType::SMALLER: 		return this->buildBinary(compPkg, expr, "sml");
	case TokenType::SMALLEREQUAL: 	return this->buildBinary(compPkg, expr, "smleql");
	case TokenType::BIGGER: 		return this->buildBinary(compPkg, expr, "bgr");
	case TokenType::BIGGEREQUAL: 	return this->buildBinary(compPkg, expr, "bgreql");

	// arithmetic binary operators 
	case TokenType::PLUS: 			return this->buildBinary(compPkg, expr, "add", &addEvaluator);
	case TokenType::MINUS: 			return this->buildBinary(compPkg, expr, "sub", &subEvaluator);
	case TokenType::STAR: 			return this->buildBinary(compPkg, expr, "mlt", &mltEvaluator);
	case TokenType::SLASH: 			return this->buildBinary(compPkg, expr, "div", &divEvaluator);
	case TokenType::MOD: 			return this->buildBinary(compPkg, expr, "mod", &modEvaluator);

	// error
	default: 						throw std::runtime_error("Invalid binary expression");
	}
}


ltnc::ExprInfo ltnc::ExprCompiler::buildBinary(
	CompilerPack & compPkg,
	std::shared_ptr<ExprBinary> expr,
	const std::string & command,
	const Evaluator * eval) const {
	

	// left and right
	ExprInfo l = this->compileExpr(compPkg, expr->l);
	ExprInfo r = this->compileExpr(compPkg, expr->r);

	// i or f for int or float
	std::string suffix = this->getSuffux(l, r);

	// try constant folding
	if(eval && compPkg.getSettings().getOptimizationLevel()) {		
		if(auto optimized = eval->optimize(l, r)) {
			return *optimized;
		}
	}

	CodeBuffer code(compPkg.getSettings().areCommentsActive());
	code << l.code;
	code << r.code;
	code << AssemblyCode(command + suffix);
	
	return ExprInfo(l.typeId, code);
}


ltnc::ExprInfo ltnc::ExprCompiler::compileUnary(CompilerPack & compPkg, std::shared_ptr<ExprUnary> expr) const {
	CodeBuffer code = compPkg.codeBuffer();
	ExprInfo exprInfo = this->compile(compPkg, expr->r);
	code << exprInfo.code;
	switch (expr->type)	{
	
	case TokenType::MINUS: {
		if(exprInfo.typeId == TypeId(TInt)){
			code << AssemblyCode("mnsi");
			return ExprInfo(exprInfo.typeId, code);
		}
		if(exprInfo.typeId == TypeId(TFloat)) {
			code << AssemblyCode("mnsf");
			return ExprInfo(exprInfo.typeId, code);
		}
		throw std::runtime_error("Invalid unary expression type for \"-\"");
	}


	case TokenType::LOG_NOT: {
		ExprInfo exprInfo = this->compile(compPkg, expr->r);
		if(exprInfo.typeId == TypeId(TInt)){
			code << AssemblyCode("lognot");
			return ExprInfo(exprInfo.typeId, code);
		}
		throw std::runtime_error("Invalid unary expression type for \"!\"");
	}


	case TokenType::BIT_NOT: {
		ExprInfo exprInfo = this->compile(compPkg, expr->r);
		if(exprInfo.typeId == TypeId(TInt)){
			code << AssemblyCode("bitnot");
			return ExprInfo(exprInfo.typeId, code);
		}
		throw std::runtime_error("Invalid unary expression type for \"!\"");
	}


	case TokenType::COPY: {
		ExprInfo exprInfo = this->compile(compPkg, expr->r);
		if(exprInfo.typeId == TypeId(TInt)){
			throw std::runtime_error("Cannot copy int");
		}
		if(exprInfo.typeId == TypeId(TFloat)) {
			throw std::runtime_error("Cannot copy flt");
		}
		code << AssemblyCode("heap::copy");
		return ExprInfo(exprInfo.typeId, code);
	}


	default:
		throw std::runtime_error("Invalid unary expression");
	}
}


ltnc::ExprInfo ltnc::ExprCompiler::compileIntLit(CompilerPack & compPkg, std::shared_ptr<ExprIntLiteral> expr) const {
	std::int64_t value = expr->number;
	CodeBuffer code = compPkg.codeBuffer();
	code << Inst::newi(value);
	return ExprInfo(TypeId(TInt), code, ConstValue(value));
}


ltnc::ExprInfo ltnc::ExprCompiler::compileFltLit(CompilerPack & compPkg, std::shared_ptr<ExprFltLiteral> expr) const {
	double value = expr->number;
	CodeBuffer code = compPkg.codeBuffer();
	code << Inst::newf(value);
	return ExprInfo(TypeId(TFloat), code, ConstValue(value));
}

ltnc::ExprInfo ltnc::ExprCompiler::compileStrLit(CompilerPack & compPkg, std::shared_ptr<ExprStrLiteral> expr) const {
	std::string string = expr->string;
	std::vector<std::string> stringParts;
	for(unsigned idx = 0; idx < string.size(); idx+=6) {
		stringParts.push_back(string.substr(idx,6));
	}
	CodeBuffer code = compPkg.codeBuffer();
	code << Comment(expr->string);
	code << AssemblyCode("string::new");
	for(const std::string & str : stringParts) {
		code << AssemblyCode("string::data '" + str + "'");
	}
	return ExprInfo(TypeId(TString), code);
}





std::string ltnc::ExprCompiler::getSuffux(const ExprInfo & l, const ExprInfo & r) const {
	// mismatch
	if(l.typeId != r.typeId) {
		throw std::runtime_error("Expression types do not match: \"" + l.code.str() + "\" and \"" + r.code.str() + "\"");
	}

	// integer
	if(l.typeId == TypeId(TInt)) {
		return "i";
	}

	// float
	if(l.typeId == TypeId(TFloat)) {
		return "f";
	}

	// if type is not int or flt
	throw std::runtime_error("Invalid Type for operation");
}


ltnc::ExprInfo ltnc::ExprCompiler::compileCall(CompilerPack & compPkg, std::shared_ptr<ExprCall> expr) const {
	CodeBuffer code(compPkg.getSettings().areCommentsActive());
	std::vector<Param> params;

	// parameter list
	for(const auto & expr : expr->paramExprs) {
		ExprInfo exprInfo = this->compileExpr(compPkg, expr);
		params.push_back(Param(exprInfo.typeId, VarId("")));
		code << exprInfo.code;
	}
	ltnc::Function fxInfo = [&expr, &params, &compPkg]() {
		try {
	 		return compPkg.getSymbolTable().match(FunctionSignature(TypeId(TRaw), expr->name, params, expr->ns));
		}
		catch(...) {
	 		return compPkg.getSymbolTable().match(FunctionSignature(TypeId(TRaw), expr->name, params, expr->ns, true));
		}
	}();
	
	code << AssemblyCode("call "  + fxInfo.jumpMark);
	return ExprInfo(fxInfo.signature.returnType, code);
}
