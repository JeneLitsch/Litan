#include "LtncComment.hxx"

ltnc::Comment::Comment(const std::string & string) 
	: string(string) {}

std::string ltnc::Comment::toString() const {
	return "// " + this->string + "\n"; 
}