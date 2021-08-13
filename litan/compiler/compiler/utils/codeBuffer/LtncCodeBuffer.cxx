#include "LtncCodeBuffer.hxx"
ltn::c::CodeBuffer::CodeBuffer(bool comments) : comments(comments) {}

ltn::c::CodeBuffer::CodeBuffer(const CodeBuffer & buffer) {
	this->buffer << buffer.buffer.rdbuf();
}


ltn::c::CodeBuffer & ltn::c::CodeBuffer::operator<<(const ICodeObject & instcode) {
	this->buffer << instcode.toString();
	return *this;
}


ltn::c::CodeBuffer & ltn::c::CodeBuffer::operator<<(const std::string & code) {
	this->buffer << code;
	return *this;
}


ltn::c::CodeBuffer & ltn::c::CodeBuffer::operator<<(const char * code) {
	this->buffer << code;
	return *this;
}


ltn::c::CodeBuffer & ltn::c::CodeBuffer::operator<<(const Comment & comment) {
	if(this->comments) {
		this->buffer << comment.toString();
	}
	return *this;
}

ltn::c::CodeBuffer & ltn::c::CodeBuffer::operator<<(const CodeBuffer & buffer) {
	this->buffer << buffer.buffer.str();
	return *this;
}


std::string ltn::c::CodeBuffer::str() const {
	return this->buffer.str();
}