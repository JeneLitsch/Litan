#pragma once 
#include "LtncDecl.hxx"
#include "LtncParserNode.hxx"

namespace ltnc {
	class ParserDeclType : public ParserNode<Type> {
	public:
		virtual std::shared_ptr<Type> eval(ParserPackage & parsePkg) const override;
	private:
	};
}