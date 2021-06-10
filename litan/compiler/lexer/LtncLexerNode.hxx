#pragma once
#include <functional>
#include "LtncLexerPackage.hxx"
namespace ltnc {
	// Node class for Lexing tree
	// Needs to be filled with a function
	// Function ptr instead of head based polymorphism
	class LexerNode {
	public:
		LexerNode(std::function<bool(LexerPackage&)> fx);
		bool eval(LexerPackage & lexPkg) const;
	private:
		std::function<bool(LexerPackage&)> fx;
	};
}