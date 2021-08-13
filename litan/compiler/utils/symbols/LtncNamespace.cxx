#include "LtncNamespace.hxx"
#include <sstream>

ltn::c::Namespace::Namespace() {}

ltn::c::Namespace::Namespace(const std::vector<std::string> & path) : path(path) {}
	
void ltn::c::Namespace::push(const std::string & ns) {
	path.push_back(ns);
}

void ltn::c::Namespace::pop() {
	path.pop_back();
}

std::string ltn::c::Namespace::str() const {
	std::stringstream ss;
	for(const std::string & step : this->path) {
		ss << step << "::";
	} 
	return ss.str();
}

std::ostream & ltn::c::operator<<(std::ostream & stream, const Namespace & ns) {
	stream << ns.str();
	return stream;
}

bool ltn::c::operator==(const Namespace & nsL, const Namespace & nsR) {
	return nsL.path == nsR.path;
}
