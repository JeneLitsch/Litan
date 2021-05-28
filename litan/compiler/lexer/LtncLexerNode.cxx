#include "LtncLexerNode.hxx"

ltnc::LexerNode::LexerNode(std::function<bool(LexerPackage&)> fx) 
: fx(fx) {}

bool ltnc::LexerNode::eval(LexerPackage & lexPkg) const {
	return this->fx(lexPkg);
}
