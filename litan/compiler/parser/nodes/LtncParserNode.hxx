#pragma once 
#include <memory>
#include <optional>
#include "LtncParserPackage.hxx"
#include "LtncAst.hxx"
#include "LtncNamespace.hxx"
namespace ltnc {
	template <class T>
	using OptRef = std::optional<std::reference_wrapper<T>>; 

	template <class AstNode>
	class ParserNode {
	public:
		virtual std::shared_ptr<AstNode> eval(ParserPackage & parsePkg) const = 0;
	private:
	};
	Namespace parserNamespace(ParserPackage & parsePkg); 
	TypeId parseType(ParserPackage & parsePkg);
}