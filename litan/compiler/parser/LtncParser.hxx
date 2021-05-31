#pragma once
#include "LtncExpr.hxx"
#include "LtncStmt.hxx"
#include "LtncToken.hxx"
#include "LtncParserPackage.hxx"

#include "LtncParserStmt.hxx"
#include "LtncParserAssign.hxx"
#include "LtncParserDeclInt.hxx"
#include "LtncParserDeclFlt.hxx"
#include "LtncParserDeclArr.hxx"
#include "LtncParserDeclStr.hxx"
#include "LtncParserFunction.hxx"

#include "LtncParserExpr.hxx"
#include "LtncParserComparison.hxx"
#include "LtncParserTerm.hxx"
#include "LtncParserProduct.hxx"
#include "LtncParserPrimary.hxx"
#include "LtncParserCall.hxx"
#include "LtncParserIfElse.hxx"
#include "LtncParserBlock.hxx"

namespace ltnc {
	class Parser {
	public:
		Parser();
		std::shared_ptr<Program> parse(const std::vector<Token> & tokens) const;
	private:


		ParserStmt stmt;
		ParserBlock block;
		ParserIfElse ifelse;
		ParserAssign assign;
		ParserDeclInt declInt;
		ParserDeclFlt declFlt;
		ParserDeclArr declArr;
		ParserDeclStr declStr;
		ParserFunction function;

		ParserExpr expr;
		ParserComparison comparison;
		ParserTerm term;
		ParserProduct product;
		ParserPrimary primary;
		ParserCall call;
	};
}