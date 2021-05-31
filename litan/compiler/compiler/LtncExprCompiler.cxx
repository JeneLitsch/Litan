#include "LtncExprCompiler.hxx"

#include "LtncAddEvaluator.hxx"
#include "LtncSubEvaluator.hxx"
#include "LtncMltEvaluator.hxx"
#include "LtncDivEvaluator.hxx"
#include "LtncModEvaluator.hxx"

ltnc::ExprInfo ltnc::ExprCompiler::compileExpr(CompilerPack & compPkg,  std::shared_ptr<Expr> expr) {
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
		return this->compileVar(compPkg, expr_);
	}
	if(auto expr_ = std::dynamic_pointer_cast<ltnc::ExprBinary>(expr)) {
		return this->compileBinary(compPkg, expr_);
	}
	if(auto expr_ = std::dynamic_pointer_cast<ltnc::ExprCall>(expr)) {
		return this->compileCall(compPkg, expr_);
	}
}


ltnc::ExprInfo ltnc::ExprCompiler::compileBinary(CompilerPack & compPkg, std::shared_ptr<ExprBinary> expr) {
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
	default: 						throw("Invalid expression"); break;
	}
}


ltnc::ExprInfo ltnc::ExprCompiler::buildBinary(
	CompilerPack & compPkg,
	std::shared_ptr<ExprBinary> expr,
	const std::string & command,
	const Evaluator & eval) {

	ExprInfo l = this->compileExpr(compPkg, expr->l);
	ExprInfo r = this->compileExpr(compPkg, expr->r);

	std::string suffix = this->getSuffux(l, r);

	if(compPkg.getSettings().getOptimizationLevel()) {		
		if(auto optimized = eval.optimize(l, r)) {
			return *optimized;
		}
	}
	return ExprInfo(l.type, l.code + r.code + command + suffix + "\n");
}


ltnc::ExprInfo ltnc::ExprCompiler::buildBinary(
	CompilerPack & compPkg,
	std::shared_ptr<ExprBinary> expr,
	const std::string & command) {
	
	ExprInfo l = this->compileExpr(compPkg, expr->l);
	ExprInfo r = this->compileExpr(compPkg, expr->r);
	std::string suffix = this->getSuffux(l, r);
	return ExprInfo(l.type, l.code + r.code + command + suffix + "\n");
}


ltnc::ExprInfo ltnc::ExprCompiler::compileIntLit(CompilerPack & compPkg, std::shared_ptr<ExprIntLiteral> expr) {
	std::int64_t value = expr->number;
	std::string code = "newi " + std::to_string(value) + "\n";
	return ExprInfo(Type::INT , code, Constant(value));
}


ltnc::ExprInfo ltnc::ExprCompiler::compileFltLit(CompilerPack & compPkg, std::shared_ptr<ExprFltLiteral> expr) {
	double value = expr->number;
	std::string code = "newf " + std::to_string(value) + "\n";
	return ExprInfo(Type::FLT, code, Constant(value));
}

ltnc::ExprInfo ltnc::ExprCompiler::compileStrLit(CompilerPack & compPkg, std::shared_ptr<ExprStrLiteral> expr) {
	std::string string = expr->string;
	std::vector<std::string> stringParts;
	for(unsigned idx = 0; idx < string.size(); idx+=6) {
		stringParts.push_back(string.substr(idx,6));
	}
	std::string code = "// " + expr->string + "\n";
	code += "string::new\n";
	for(const std::string & str : stringParts) {
		code += "string::data '" + str + "'\n";
	}
	return ExprInfo(Type::STR, code);
}

ltnc::ExprInfo ltnc::ExprCompiler::compileVar(CompilerPack & compPkg, std::shared_ptr<ExprVar> expr) {
	Var var = compPkg.getScopes().get().getVar(expr->name);
	return ExprInfo(var.type, "load " + std::to_string(var.addr) + "\n");
}


std::string ltnc::ExprCompiler::getSuffux(const ExprInfo & l, const ExprInfo & r) {
	if(l.type != r.type) {
		throw std::runtime_error("Expression types do not match: \"" + l.code + "\" and \"" + r.code + "\"");
	}
	switch (l.type.type) {
		case Type::INT: return "i";
		case Type::FLT: return "f";
		default: throw std::runtime_error("Invalid Type for operation");
	}
}


ltnc::ExprInfo ltnc::ExprCompiler::compileCall(CompilerPack & compPkg, std::shared_ptr<ExprCall> expr) {
	std::string code;
	std::vector<Param> params;

	// parameter list
	for(const auto & expr : expr->paramExprs) {
		ExprInfo exprInfo = this->compileExpr(compPkg, expr);
		params.push_back(Param(exprInfo.type, ""));
		code += exprInfo.code;
	}

	if(auto fxInfo = compPkg.matchFunction(FxSignature(Type::VOI, expr->name, params))) {
		// create jump to fx
		code += "call "  + fxInfo->jumpMark + "\n";
		return ExprInfo(fxInfo->signature.returnType, code);
	}
	throw std::runtime_error("No matching function for: " + expr->name);
}
