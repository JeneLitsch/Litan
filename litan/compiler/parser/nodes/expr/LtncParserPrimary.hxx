#pragma once
#include "LtncExpr.hxx"
#include "LtncParserNode.hxx"

namespace ltnc {
	// Parses primary expression 
	// literals, call and identifier
	class ParserPrimary : public ParserNode<Expr> {
	public:
		void connect(
			const ParserNode<ExprCall> & call,
			const ParserNode<ExprVar> & var);

		virtual std::shared_ptr<Expr> eval(
			ParserPackage & parsePkg) const override;
	
	private:
		const ParserNode<ExprCall> * call;
		const ParserNode<ExprVar> * var;
	};
}