#include "LtncInst.hxx"
#include <sstream>
#include "LtncCodeBuffer.hxx"
ltn::c::Inst::Inst(const std::string & string) 
	: string(string) {}

std::string ltn::c::Inst::toString() const {
	return this->string + "\n";
}

ltn::c::Inst ltn::c::Inst::stackalloc(std::uint32_t count) {
	return Inst("stackalloc " + std::to_string(count));
}

ltn::c::Inst ltn::c::Inst::call(const std::string & jumpMark) {
	return Inst("call " + jumpMark);
}

ltn::c::Inst ltn::c::Inst::newl(std::uint32_t value) {
	return Inst("newl " + std::to_string(value));
}

ltn::c::Inst ltn::c::Inst::newu(std::uint32_t value) {
	return Inst("newu " + std::to_string(value));
}

ltn::c::Inst ltn::c::Inst::newi(std::uint64_t value) {
	return Inst("newi " + std::to_string(value));
}

ltn::c::Inst ltn::c::Inst::newi(std::int64_t value) {
	return Inst("newi " + std::to_string(value));
}

ltn::c::Inst ltn::c::Inst::newf(double value) {
	return Inst("newf " + std::to_string(value));
}

ltn::c::Inst ltn::c::Inst::got0(const std::string & markStr) {
	return Inst("goto " + markStr);
}

ltn::c::Inst ltn::c::Inst::mark(const std::string & markStr) {
	return Inst("-> " + markStr);
}

ltn::c::Inst ltn::c::Inst::load(std::uint32_t value) {
	return Inst("load " + std::to_string(value));
}

ltn::c::Inst ltn::c::Inst::store(std::uint32_t value) {
	return Inst("store " + std::to_string(value));
}

ltn::c::Inst ltn::c::Inst::allocateStruct(std::size_t size){
	return Inst("heap::allocate::struct " + std::to_string(size));
}

ltn::c::Inst ltn::c::Inst::stringData(const std::string & str) {
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

ltn::c::Inst ltn::c::Inst::structRead(std::uint32_t addr) {
	return Inst("struct::read " + std::to_string(addr));

}

ltn::c::Inst ltn::c::Inst::structWrite(std::uint32_t addr) {
	return Inst("struct::write " + std::to_string(addr));
}

