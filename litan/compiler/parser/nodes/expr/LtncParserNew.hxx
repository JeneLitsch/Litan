#pragma once 
#include "LtncParserNode.hxx"
#include "LtncExpr.hxx"
namespace ltnc {
	class ParserNew : public ParserNode<ExprNew> {
	public:
		virtual std::shared_ptr<ExprNew> eval(ParserPackage & parsePkg) const override;
	};
}