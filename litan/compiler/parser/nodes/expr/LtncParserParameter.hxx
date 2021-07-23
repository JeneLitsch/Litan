#pragma once 
#include <vector>
#include <memory>
#include "LtncExpr.hxx"
#include "LtncParserNode.hxx"
namespace ltnc {
	class ParserExpr;
	// Parses a call operation like "->foo()"
	class ParserParameter : public ParserNode<std::vector<std::shared_ptr<Expr>>> {
	public:
		ParserParameter(const ParserExpr & expr);
		virtual std::shared_ptr<std::vector<std::shared_ptr<Expr>>> eval(ParserPackage & parsePkg) const override;
	private:
		const ParserExpr * expr;
	};
}