#include "LtnStackFrame.hxx"

ltn::StackFrame::StackFrame() {
	this->jumpback = 0;
}
ltn::StackFrame::StackFrame(std::uint64_t jumpback) {
	this->jumpback = jumpback;
}