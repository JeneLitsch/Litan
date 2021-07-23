#pragma once
#include "LtncExpr.hxx"
#include "LtncParserNode.hxx"

namespace ltnc {
	// Parses primary expression 
	// literals, call and identifier
	class ParserPrimary : public ParserNode<Expr> {
	public:
		ParserPrimary(
			const ParserNode<ExprCall> & call,
			const ParserNode<ExprVar> & var,
			const ParserNode<Expr> & expr);

		virtual std::shared_ptr<Expr> eval(
			ParserPackage & parsePkg) const override;
	
	private:
		const ParserNode<ExprCall> * call;
		const ParserNode<ExprVar> * var;
		const ParserNode<Expr> * expr;
	};
}