#pragma once 
#include "LtncDecl.hxx"
#include "LtncParserNode.hxx"

namespace ltnc {
	class ParserDeclArr : public ParserNode<DeclVar> {
	public:
		virtual std::shared_ptr<DeclVar> eval(ParserPackage & parsePkg) const override;
	private:
	};
}