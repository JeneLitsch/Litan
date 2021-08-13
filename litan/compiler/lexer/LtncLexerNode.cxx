#include "LtncLexerNode.hxx"

ltn::c::LexerNode::LexerNode(std::function<bool(LexerPackage&)> fx) 
: fx(fx) {}

bool ltn::c::LexerNode::eval(LexerPackage & lexPkg) const {
	// run contained function
	return this->fx(lexPkg);
}
