#pragma once 
#include <memory>
#include "LtncParserNode.hxx"
#include "LtncExpr.hxx"
namespace ltnc {
	class ParserParameter;
	class ParserNew : public ParserNode<ExprNew> {
	public:
		void connect(const ParserParameter & exprParam);
		virtual std::shared_ptr<ExprNew> eval(ParserPackage & parsePkg) const override;
	private:
		const ParserParameter * exprParam;
	};
}