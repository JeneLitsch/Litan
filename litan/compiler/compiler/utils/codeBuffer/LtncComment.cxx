#include "LtncComment.hxx"

ltn::c::Comment::Comment(const std::string & string) 
	: string(string) {}

std::string ltn::c::Comment::toString() const {
	return "// " + this->string + "\n"; 
}