#pragma once
#include "LtncExpr.hxx"
#include "LtncParserNode.hxx"

namespace ltnc {
	class ParserExpr : public ParserNode<Expr> {
	public:
		void connect(const ParserNode<Expr> & comparison);
		virtual std::shared_ptr<Expr> eval(ParserPackage & parsePkg) const override;
	
	private:
		const ParserNode<Expr> * comparison;
	};
}