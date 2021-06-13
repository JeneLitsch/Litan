#pragma once
#include "LtncExpr.hxx"
#include "LtncStmt.hxx"
#include "LtncToken.hxx"
#include "LtncParserPackage.hxx"

#include "LtncParserStmt.hxx"
#include "LtncParserAssign.hxx"
#include "LtncParserDeclVar.hxx"
#include "LtncParserDeclType.hxx"
#include "LtncParserDeclStruct.hxx"
#include "LtncParserFunction.hxx"

#include "LtncParserExpr.hxx"
#include "LtncParserComparison.hxx"
#include "LtncParserTerm.hxx"
#include "LtncParserProduct.hxx"
#include "LtncParserUnary.hxx"
#include "LtncParserPrimary.hxx"
#include "LtncParserCall.hxx"
#include "LtncParserVar.hxx"
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
		ParserDeclVar declVar;
		ParserDeclType declType;
		ParserDeclStruct declStruct;
		ParserFunction function;

		ParserExpr expr;
		ParserComparison comparison;
		ParserTerm term;
		ParserProduct product;
		ParserUnary unary;
		ParserPrimary primary;
		ParserCall call;
		ParserVar var;
	};
}