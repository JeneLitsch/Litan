#pragma once 
#include "LtncDecl.hxx"
#include "LtncParserNode.hxx"

namespace ltnc {
	class ParserDeclStruct : public ParserNode<DeclStruct> {
	public:
		ParserDeclStruct(const ParserNode<DeclVar> & declVar);
		virtual std::shared_ptr<DeclStruct> eval(ParserPackage & parsePkg) const override;
	private:
		const ParserNode<DeclVar> & declVar;
	};
}