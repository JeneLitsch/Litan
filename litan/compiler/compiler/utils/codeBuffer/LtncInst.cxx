#include "LtncInst.hxx"
#include <sstream>
#include "LtncCodeBuffer.hxx"
ltnc::Inst::Inst(const std::string & string) 
	: string(string) {}

std::string ltnc::Inst::toString() const {
	return this->string + "\n";
}

ltnc::Inst ltnc::Inst::newl(std::uint32_t value) {
	return Inst("newl " + std::to_string(value));
}

ltnc::Inst ltnc::Inst::newu(std::uint32_t value) {
	return Inst("newu " + std::to_string(value));
}

ltnc::Inst ltnc::Inst::newi(std::uint64_t value) {
	return Inst("newi " + std::to_string(value));
}

ltnc::Inst ltnc::Inst::newi(std::int64_t value) {
	return Inst("newi " + std::to_string(value));
}

ltnc::Inst ltnc::Inst::newf(double value) {
	return Inst("newf " + std::to_string(value));
}



ltnc::Inst ltnc::Inst::load(std::uint32_t value) {
	return Inst("load " + std::to_string(value));
}

ltnc::Inst ltnc::Inst::store(std::uint32_t value) {
	return Inst("store " + std::to_string(value));
}


ltnc::Inst ltnc::Inst::stringData(const std::string & str) {
	if(str.size() > 6) {
		CodeBuffer code(false);
		for(unsigned idx = 0; idx < str.size(); idx+=6) {
			code << stringData(str.substr(idx,6));
		}
		return Inst(code.str());
	}
	else {
		std::stringstream ss;
		ss << std::hex;
		for(char chr : str) {
			ss << "0x" << int(chr) << " ";
		}
		return Inst("string::data " + ss.str());
	}
}
