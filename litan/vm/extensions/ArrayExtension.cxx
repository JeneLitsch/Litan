#include "ArrayExtension.hxx"

ltn::ArrayExtension::ArrayExtension(Environment & env) 
: env(env){
	this->nextID = 0;
}


void ltn::ArrayExtension::call(std::uint8_t funct_){
	ArrayFunct funct = static_cast<ArrayFunct>(funct_);

	switch (funct)
	{
	case ArrayFunct::NEW: this->nEw(); break;
	case ArrayFunct::DEL: this->del(); break;
	case ArrayFunct::ADD: this->add(); break;
	case ArrayFunct::POP: this->pop(); break;
	case ArrayFunct::SET: this->set(); break;
	case ArrayFunct::GET: this->get(); break;
	case ArrayFunct::CLR: this->clr(); break;
	case ArrayFunct::LEN: this->len(); break;
	
	default:
		throw std::runtime_error("ArrayExtension: Unknow functCode");
	}
}

std::vector<std::uint64_t> & ltn::ArrayExtension::getBuffer(std::uint64_t addr){
	if(this->buffers.contains(addr)){
		return buffers.at(addr);
	}
	else{
		throw std::runtime_error("Access Violation at id: " + std::to_string(addr));
	}
}



void ltn::ArrayExtension::nEw(){
	std::uint64_t addr;

	// determine id
	// new id
	if(this->resuseableIDs.empty()){
		addr = this->nextID;
		this->nextID++;
	}
	// reuse id
	else{
		addr = this->resuseableIDs.front();
		this->resuseableIDs.pop();
	}

	this->buffers.insert({addr, std::vector<std::uint64_t>()});
	// push pointer
	this->env.acc.push(addr);
}

void ltn::ArrayExtension::del(){
	std::uint64_t addr = this->env.acc.pop();
	if(this->buffers.contains(addr)){
		this->resuseableIDs.push(addr);
		this->buffers.erase(addr);
	}
	else{
		throw std::runtime_error("Access Violation at id: " + std::to_string(addr));
	}

}

void ltn::ArrayExtension::clr(){
	std::uint64_t addr = env.acc.pop();
	this->getBuffer(addr).clear();
}

void ltn::ArrayExtension::get(){
	std::uint64_t idx = env.acc.pop();
	std::uint64_t addr = env.acc.pop();
	auto & buffer = this->getBuffer(addr);
	if(idx < buffer.size()){
		env.acc.push(buffer[idx]);
	}
	else{
		throw std::runtime_error("Access Violation" 
			"at id: " + std::to_string(addr) + " "
			"at index: " + std::to_string(idx));
	}
}

void ltn::ArrayExtension::set(){
	std::uint64_t value = env.acc.pop();
	std::uint64_t idx = env.acc.pop();
	std::uint64_t addr = env.acc.pop();
	auto & buffer = this->getBuffer(addr);
	if(idx < buffer.size()){
		buffer[idx] = value;
	}
	else{
		throw std::runtime_error("Access Violation" 
			"at id: " + std::to_string(addr) + " "
			"at index: " + std::to_string(idx));
	}
}

void ltn::ArrayExtension::add(){
	std::uint64_t value = env.acc.pop();
	std::uint64_t addr = env.acc.pop();
	this->getBuffer(addr).push_back(value);
}

void ltn::ArrayExtension::pop(){
	std::uint64_t addr = env.acc.pop();
	auto & buffer = this->getBuffer(addr);
	if(buffer.empty()) {
		throw std::runtime_error("Access Violation at id: " + std::to_string(addr) + " attempt to pop from empty buffer");
	}
	env.acc.push(buffer.back());
	buffer.pop_back();
}

void ltn::ArrayExtension::len(){
	std::uint64_t addr = env.acc.pop();
	env.acc.push(this->getBuffer(addr).size());
}

void ltn::ArrayExtension::setBuffer(const std::vector<std::uint64_t> & buffer){
	this->nEw();
	this->getBuffer(env.acc.pop()) = buffer;
}
