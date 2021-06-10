#pragma once 
#include "LtncParserNode.hxx"

namespace ltnc {
	class ParserExpr;
	// Parses a call operation like "->foo()"
	class ParserCall : public ParserNode<ExprCall> {
	public:
		void connect(const ParserExpr & expr);
		virtual std::shared_ptr<ExprCall> eval(ParserPackage & parsePkg) const override;
		const ParserExpr * expr;
	private:
		// matches parameters
		std::vector<std::shared_ptr<Expr>> evelParameters(ParserPackage & parsePkg) const;
	};
}