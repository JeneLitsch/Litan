#pragma once 
#include "LtncParserNode.hxx"
#include "LtncDecl.hxx"
namespace ltnc {
	class ParserDeclInt : public ParserNode<DeclVar> {
	public:
		ParserDeclInt() {};
		virtual std::shared_ptr<DeclVar> eval(ParserPackage & parsePkg) const override;
	};
}