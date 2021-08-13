#include "LtnVM.hxx"

// jump and push address to adrStack
void ltn::vm::VM::call(){
	this->env.stack.call(this->env.getPc());
	this->env.jump(this->getArg56());
}
// jump without pushign the address to adrStack
void ltn::vm::VM::got0(){
	this->env.jump(this->getArg56());
}
// pop last address from adrStack and jump to it 
void ltn::vm::VM::rtrn(){
	this->env.ip = this->env.bytecode.start + this->env.stack.pop();
}
// skip one instruction if value popped is 0
void ltn::vm::VM::ifsk(){
	if(!this->env.acc.popI()) {
		this->env.ip++;
	}
}


// Loop instruction
void ltn::vm::VM::loopRange() {
	const std::int64_t end = env.acc.popI();
	const std::int64_t start = env.acc.popI();
	this->env.loops.push(Loop(this->env.getPc(), start, end));
}

void ltn::vm::VM::loopInf() {
	this->env.loops.push(Loop(this->env.getPc()));
}

void ltn::vm::VM::loopCont() {
	Loop & loop = this->env.loops.top();
	// stop if end of loop is reached
	if(loop.atEnd()){
		return this->env.loops.pop();
	}
	// jump back
	env.jump(loop.addr);
	// increment
	loop.idx++;
}

void ltn::vm::VM::loopStop() {
	this->env.loops.pop();
}

void ltn::vm::VM::loopIdx() {
	env.acc.push(this->env.loops.top().idx);
}
