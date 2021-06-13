#pragma once 
#include "LtncParserNode.hxx"

namespace ltnc {
	// Parses a call operation like "->foo()"
	class ParserVar : public ParserNode<ExprVar> {
	public:
		virtual std::shared_ptr<ExprVar> eval(ParserPackage & parsePkg) const override;
	};
}