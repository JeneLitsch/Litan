#include "LtncNamespace.hxx"
#include <sstream>

ltnc::Namespace::Namespace() {}

ltnc::Namespace::Namespace(const std::vector<std::string> & path) : path(path) {}
	
void ltnc::Namespace::push(const std::string & ns) {
	path.push_back(ns);
}

void ltnc::Namespace::pop() {
	path.pop_back();
}

std::string ltnc::Namespace::str() const {
	std::stringstream ss;
	for(const std::string & step : this->path) {
		ss << step << "::";
	} 
	return ss.str();
}

std::ostream & ltnc::operator<<(std::ostream & stream, const Namespace & ns) {
	stream << ns.str();
	return stream;
}

bool ltnc::operator==(const Namespace & nsL, const Namespace & nsR) {
	return nsL.path == nsR.path;
}
