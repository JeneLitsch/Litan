#pragma once 
#include "LtncParserNode.hxx"
namespace ltnc {
	class ParserParameter;
	// Parses a call operation like "->foo()"
	class ParserCall : public ParserNode<ExprCall> {
	public:
		ParserCall(const ParserParameter & exprParam);
		virtual std::shared_ptr<ExprCall> eval(ParserPackage & parsePkg) const override;
	private:
		const ParserParameter * exprParam;
	};
}