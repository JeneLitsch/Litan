#pragma once 
#include "LtncDecl.hxx"
#include "LtncParserNode.hxx"

namespace ltnc {
	class ParserDeclFlt : public ParserNode<DeclVar> {
	public:
		virtual std::shared_ptr<DeclVar> eval(ParserPackage & parsePkg) const override;
	private:
	};
}