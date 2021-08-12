#include "LtnErrorReporter.hxx"
#include <sstream>

ltn::ErrorReporter::ErrorReporter()
	: Error("") {

}

ltn::ErrorReporter & ltn::ErrorReporter::operator<<(const Error & error) {
	if(const ErrorReporter * err = dynamic_cast<const ErrorReporter*>(&error)) {
		for(const ltn::Error & suberr : err->suberrors) {
			this->suberrors.push_back(suberr);
		}
	}
	else {
		this->suberrors.push_back(error);
	}
	return *this;
}


bool ltn::ErrorReporter::throwable() const {
	return !this->suberrors.empty();
}

std::string ltn::ErrorReporter::str() const {
	std::stringstream ss;
	for(const ltn::Error & suberr : this->suberrors) {
		ss << suberr.what() << "\n";
	}
	return ss.str();
}