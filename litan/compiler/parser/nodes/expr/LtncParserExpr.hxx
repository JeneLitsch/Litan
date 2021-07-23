#pragma once
#include "LtncExpr.hxx"
#include "LtncParserNode.hxx"

namespace ltnc {
	class ParserExpr : public ParserNode<Expr> {
	public:
		ParserExpr(
			const ParserNode<Expr> & comparison,
			const ParserNode<ExprNew> & newstruct,
			const ParserNode<ExprDel> & delstruct);
		virtual std::shared_ptr<Expr> eval(ParserPackage & parsePkg) const override;
	
	private:
		const ParserNode<Expr> * comparison;
		const ParserNode<ExprNew> * newstruct;
		const ParserNode<ExprDel> * delstruct;
	};
}