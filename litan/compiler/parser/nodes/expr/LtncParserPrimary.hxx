#pragma once
#include "LtncExpr.hxx"
#include "LtncParserNode.hxx"

namespace ltnc {
	class ParserPrimary : public ParserNode<Expr> {
	public:
		void connect(const ParserNode<ExprCall> & call);
		virtual std::shared_ptr<Expr> eval(ParserPackage & parsePkg) const override;
	
	private:
		const ParserNode<ExprCall> * call;
	};
}