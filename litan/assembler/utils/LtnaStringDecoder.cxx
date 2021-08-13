#include "LtnaStringDecoder.hxx"
#include <stdexcept>

std::string ltn::a::StringDecoder::decode(const std::vector<std::string> & args) {
	std::string encodedString;
	for(const std::string & arg : args) {
		encodedString += arg + " ";
	}
	encodedString.pop_back();
	if(encodedString.front() != '\'' || encodedString.back() != '\'') {
		throw std::runtime_error("String is not delimited");
	}
	encodedString.pop_back();
	encodedString.erase(encodedString.begin());

	std::vector<std::string> encodedChars;
	
	for(unsigned idx = 0; idx < encodedString.size(); idx++) {
		char chr = encodedString[idx];
		if(chr == '\\') {
			encodedChars.push_back(encodedString.substr(idx,2));
			idx++;
		}
		else {
			encodedChars.push_back(encodedString.substr(idx,1));
		}
	}

	std::string decodedStr;
	for(const std::string & encodedChar : encodedChars) {
		if(encodedChar.size() == 1) {
			decodedStr.push_back(encodedChar[0]);
		}
		else {
			if(encodedChar == "\\n") {
				decodedStr.push_back('\n');
			}
			if(encodedChar == "\\t") {
				decodedStr.push_back('\t');
			}
			if(encodedChar == "\\\"") {
				decodedStr.push_back('"');
			}
			if(encodedChar == "\\\\") {
				decodedStr.push_back('\\');
			}
		}
	}
	return decodedStr;
}