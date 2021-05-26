#include "LoopExtension.hxx"

void ltn::LoopExtension::call(std::uint8_t funct_) {
	LoopFunct funct = static_cast<LoopFunct>(funct_);
	switch (funct) {
	case LoopFunct::INF: this->inf(); break;
	case LoopFunct::RANGE: this->range(); break;
	case LoopFunct::CONT: this->cont(); break;
	case LoopFunct::STOP: this->stop(); break;
	case LoopFunct::IDX: this->idx(); break;
	
	default:
		throw std::runtime_error("LoopExtension: Unknown funct: " + std::to_string(funct_));
	}
}

void ltn::LoopExtension::reset(){
	this->loops = std::stack<Loop>();
}

void ltn::LoopExtension::inf(){
	this->loops.push(Loop(env.pc));
}

void ltn::LoopExtension::range(){
	std::int64_t end = env.pollI();
	std::int64_t start = env.pollI();
	this->loops.push(Loop(env.pc, start, end));
}

void ltn::LoopExtension::stop(){
	this->loops.pop();
}

void ltn::LoopExtension::cont(){
	Loop & loop = this->loops.top();
	// stop if end of loop is reached
	if(loop.atEnd()){
		this->stop();
	}
	else{
		// jump back
		env.pc = loop.addr;
		// increment
		loop.idx++;
	}
}

void ltn::LoopExtension::idx(){
	env.acc.push(this->loops.top().idx);
}