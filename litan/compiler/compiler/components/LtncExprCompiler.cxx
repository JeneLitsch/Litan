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


ltnc::ExprCompiler::ExprCompiler(
	const CnstCompiler & cnstCompiler,
	const DstrCompiler & dstrCompiler,
	const VariCompiler & variCompiler) 
	: 
	cnstCompiler(cnstCompiler),
	dstrCompiler(dstrCompiler),
	variCompiler(variCompiler) {}


ltnc::ExprInfo ltnc::ExprCompiler::compile(CompilerPack & compPkg, const std::shared_ptr<Expr> & expr) const {
	return this->compileExpr(compPkg, expr);
}


ltnc::ExprInfo ltnc::ExprCompiler::compileExpr(CompilerPack & compPkg,  std::shared_ptr<Expr> expr) const {
	if(auto expr_ = std::dynamic_pointer_cast<ltnc::ExprNew>(expr)) {
		return this->cnstCompiler.compile(compPkg, expr_);
	}
	if(auto expr_ = std::dynamic_pointer_cast<ltnc::ExprDel>(expr)) {
		return this->dstrCompiler.compile(compPkg, expr_);
	}
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
	switch (expr->type)	{

	// comparision operator
	case TokenType::EQUAL:			return this->buildBinary(compPkg, expr, "eql");
	case TokenType::UNEQUAL: 		return this->buildBinary(compPkg, expr, "uneql");
	case TokenType::SMALLER: 		return this->buildBinary(compPkg, expr, "sml");
	case TokenType::SMALLEREQUAL: 	return this->buildBinary(compPkg, expr, "smleql");
	case TokenType::BIGGER: 		return this->buildBinary(compPkg, expr, "bgr");
	case TokenType::BIGGEREQUAL: 	return this->buildBinary(compPkg, expr, "bgreql");

	// arithmetic binary operators 
	case TokenType::PLUS: 			return this->buildBinary(compPkg, expr, "add", AddEvaluator());
	case TokenType::MINUS: 			return this->buildBinary(compPkg, expr, "sub", SubEvaluator());
	case TokenType::STAR: 			return this->buildBinary(compPkg, expr, "mlt", MltEvaluator());
	case TokenType::SLASH: 			return this->buildBinary(compPkg, expr, "div", DivEvaluator());
	case TokenType::MOD: 			return this->buildBinary(compPkg, expr, "mod", ModEvaluator());

	// error
	default: 						throw std::runtime_error("Invalid binary expression");
	}
}


ltnc::ExprInfo ltnc::ExprCompiler::buildBinary(
	CompilerPack & compPkg,
	std::shared_ptr<ExprBinary> expr,
	const std::string & command,
	const Evaluator & eval) const {
	

	// left and right
	ExprInfo l = this->compileExpr(compPkg, expr->l);
	ExprInfo r = this->compileExpr(compPkg, expr->r);

	// i or f for int or float
	std::string suffix = this->getSuffux(l, r);

	// try constant folding
	if(compPkg.getSettings().getOptimizationLevel()) {		
		if(auto optimized = eval.optimize(l, r)) {
			return *optimized;
		}
	}

	CodeBuffer code(compPkg.getSettings().areCommentsActive());
	code << l.code;
	code << r.code;
	code << AssemblyCode(command + suffix);
	
	return ExprInfo(l.type, code);
}


ltnc::ExprInfo ltnc::ExprCompiler::buildBinary(
	CompilerPack & compPkg,
	std::shared_ptr<ExprBinary> expr,
	const std::string & command) const {
	// left and right expr
	ExprInfo l = this->compileExpr(compPkg, expr->l);
	ExprInfo r = this->compileExpr(compPkg, expr->r);

	// i or f for int or float
	std::string suffix = this->getSuffux(l, r);

	CodeBuffer code(compPkg.getSettings().areCommentsActive());
	code << l.code;
	code << r.code;
	code << AssemblyCode(command + suffix);
	
	return ExprInfo(l.type, code);
}

ltnc::ExprInfo ltnc::ExprCompiler::compileUnary(CompilerPack & compPkg, std::shared_ptr<ExprUnary> expr) const {
	CodeBuffer code = compPkg.codeBuffer();
	if(expr->type == TokenType::MINUS) {
		ExprInfo exprInfo = this->compile(compPkg, expr->r);
		if(exprInfo.type == "int"){
			code << exprInfo.code;
			code << AssemblyCode("mnsi");
			return ExprInfo(exprInfo.type, code);
		}
		if(exprInfo.type == "flt") {
			code << exprInfo.code;
			code << AssemblyCode("mnsf");
			return ExprInfo(exprInfo.type, code);
		}
		throw std::runtime_error("Invalid unary expression type for \"-\"");
	}
	throw std::runtime_error("Invalid unary expression");
}


ltnc::ExprInfo ltnc::ExprCompiler::compileIntLit(CompilerPack & compPkg, std::shared_ptr<ExprIntLiteral> expr) const {
	std::int64_t value = expr->number;
	CodeBuffer code = compPkg.codeBuffer();
	code << Inst::newi(value);
	return ExprInfo(Type("int"), code, Constant(value));
}


ltnc::ExprInfo ltnc::ExprCompiler::compileFltLit(CompilerPack & compPkg, std::shared_ptr<ExprFltLiteral> expr) const {
	double value = expr->number;
	CodeBuffer code = compPkg.codeBuffer();
	code << Inst::newf(value);
	return ExprInfo(Type("flt"), code, Constant(value));
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
		code << AssemblyCode("string::data '" + str);
	}
	return ExprInfo(Type("str"), code);
}





std::string ltnc::ExprCompiler::getSuffux(const ExprInfo & l, const ExprInfo & r) const {
	// mismatch
	if(l.type != r.type) {
		throw std::runtime_error("Expression types do not match: \"" + l.code.str() + "\" and \"" + r.code.str() + "\"");
	}

	// integer
	if(l.type == "int") {
		return "i";
	}

	// float
	if(l.type == "flt") {
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
		params.push_back(Param(exprInfo.type, ""));
		code << exprInfo.code;
	}

	if(auto fxInfo = compPkg.matchFunction(FxSignature(Type("voi"), expr->name, params))) {
		// create jump to fx
		code << AssemblyCode("call "  + fxInfo->jumpMark);
		return ExprInfo(fxInfo->signature.returnType, code);
	}
	throw std::runtime_error("No matching function for: " + expr->name);
}
