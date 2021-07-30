#include "LtnVM.hxx"

// jump and push address to adrStack
void ltn::VM::call(){
	this->env.stack.push(this->env.pc);
	this->env.pc = this->getArg56();
}
// jump without pushign the address to adrStack
void ltn::VM::got0(){
	this->env.pc = this->getArg56();
}
// pop last address from adrStack and jump to it 
void ltn::VM::rtrn(){
	this->env.pc = this->env.stack.get().jumpback;
	this->env.stack.pop();
}
// skip one instruction if value popped is 0
void ltn::VM::ifsk(){
	if(this->env.acc.popI() == 0){
		this->env.pc++;
	}
}


// Loop instruction
void ltn::VM::loopRange() {
	std::int64_t end = env.acc.popI();
	std::int64_t start = env.acc.popI();
	this->env.loops.push(Loop(env.pc, start, end));
}

void ltn::VM::loopInf() {
	this->env.loops.push(Loop(env.pc));
}

void ltn::VM::loopCont() {
	Loop & loop = this->env.loops.top();
	// stop if end of loop is reached
	if(loop.atEnd()){
		this->env.loops.pop();
	}
	else{
		// jump back
		env.pc = loop.addr;
		// increment
		loop.idx++;
	}
}

void ltn::VM::loopStop() {
	this->env.loops.pop();
}

void ltn::VM::loopIdx() {
	env.acc.push(this->env.loops.top().idx);
}
