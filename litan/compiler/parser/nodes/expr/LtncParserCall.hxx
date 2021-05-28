#pragma once 
#include "LtncParserNode.hxx"

namespace ltnc {
	class ParserExpr;
	class ParserCall : public ParserNode<ExprCall> {
	public:
		void connect(const ParserExpr & expr);
		virtual std::shared_ptr<ExprCall> eval(ParserPackage & parsePkg) const override;
		const ParserExpr * expr;
	};
}