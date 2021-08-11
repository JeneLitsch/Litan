#include "LtnCumulatedError.hxx"
#include <sstream>
ltn::CumulatedError::CumulatedError()
	: Error("") {

}

void ltn::CumulatedError::pushError(const Error & error) {
	if(const CumulatedError * err = dynamic_cast<const CumulatedError*>(&error)) {
		for(const ltn::Error & suberr : err->suberrors) {
			this->suberrors.push_back(suberr);
		}
	}
	else {
		this->suberrors.push_back(error);
	}
}


bool ltn::CumulatedError::throwable() const {
	return !this->suberrors.empty();
}

std::string ltn::CumulatedError::str() const {
	std::stringstream ss;
	for(const ltn::Error & suberr : this->suberrors) {
		ss << suberr.what() << "\n";
	}
	return ss.str();
}