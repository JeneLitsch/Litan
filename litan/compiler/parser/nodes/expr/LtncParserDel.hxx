#pragma once 
#include "LtncParserNode.hxx"
#include "LtncExpr.hxx"
namespace ltnc {
	class ParserDel : public ParserNode<ExprDel> {
	public:
		ParserDel(const ParserNode<ExprVar> & exprVar);
		virtual std::shared_ptr<ExprDel> eval(ParserPackage & parsePkg) const override;

	private:
		const ParserNode<ExprVar> * exprVar;
	};
}