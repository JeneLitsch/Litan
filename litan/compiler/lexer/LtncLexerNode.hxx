#pragma once
#include <functional>
#include "LtncLexerPackage.hxx"
namespace ltnc {
	class LexerNode {
	public:
		LexerNode(std::function<bool(LexerPackage&)> fx);
		bool eval(LexerPackage & lexPkg) const;
	private:
		std::function<bool(LexerPackage&)> fx;
	};
}