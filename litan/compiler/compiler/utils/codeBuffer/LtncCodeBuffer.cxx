#include "LtncCodeBuffer.hxx"
ltnc::CodeBuffer::CodeBuffer(bool comments) : comments(comments) {}

ltnc::CodeBuffer::CodeBuffer(const CodeBuffer & buffer) {
	this->buffer << buffer.buffer.rdbuf();
}


ltnc::CodeBuffer & ltnc::CodeBuffer::operator<<(const ICodeObject & instcode) {
	this->buffer << instcode.toString();
	return *this;
}


ltnc::CodeBuffer & ltnc::CodeBuffer::operator<<(const std::string & code) {
	this->buffer << code;
	return *this;
}


ltnc::CodeBuffer & ltnc::CodeBuffer::operator<<(const char * code) {
	this->buffer << code;
	return *this;
}


ltnc::CodeBuffer & ltnc::CodeBuffer::operator<<(const Comment & comment) {
	if(this->comments) {
		this->buffer << comment.toString();
	}
	return *this;
}

ltnc::CodeBuffer & ltnc::CodeBuffer::operator<<(const CodeBuffer & buffer) {
	this->buffer << buffer.buffer.str();
	return *this;
}


std::string ltnc::CodeBuffer::str() const {
	return this->buffer.str();
}