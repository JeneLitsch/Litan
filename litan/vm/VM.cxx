#include "VM.hxx"
#include <iostream>
#include <cmath>
#include <sstream>
#include <iomanip>

// memorySize and stackLimit in 64bit blocks
ltn::VM::VM() :
	 	arrayExt(this->env), 
		loopExt(this->env) {
	
	this->reset();
}

void ltn::VM::installExtension(IExtension & ext, Slot slot){
	this->extensions[static_cast<unsigned>(slot)] = &ext;
	ext.setEnvironsment(this->env);
}


void ltn::VM::init(const std::vector<std::uint64_t> & byteCode){
	this->env.instructions = byteCode;
	this->reset();
}


std::array<std::uint64_t, 256> ltn::VM::newStackFrame(){
	std::array<std::uint64_t, 256> frame;
	frame.fill(0);
	return frame;
}


void ltn::VM::reset(){
	

	//reset 
	this->env.pc = 0;
	this->env.stack_ptr = 0;
	this->env.memory = {};

	this->loopExt.reset();
	this->arrayExt.reset();

	// clear stack
	this->env.acc.reset();
	this->env.adr.reset();
}

ltn::VM::Status ltn::VM::run(){
	Status exitStatus = this->execute();
	if(exitStatus == Status::EXITED || exitStatus == Status::ERROR){
		this->reset();
	}
	return exitStatus;
}


void ltn::VM::decode(){
	std::uint64_t inst = this->env.instructions[this->env.pc];
	this->env.pc++;
	this->opcode = static_cast<InstCode>(std::uint8_t((inst) & 0xff));
	this->currentInstruction = inst;

	// std::cout << int(opcode) << std::endl;
}



ltn::VM::Status ltn::VM::execute(){
	while(true){
		this->decode();

		switch (opcode) {
		case InstCode::EXIT: return Status::EXITED;
		case InstCode::SUSPEND: return Status::SUSPENDED;
		case InstCode::ERROR: return Status::ERROR;
		case InstCode::LOAD: this->load(); break;
		case InstCode::STORE: this->store(); break;
		case InstCode::COPY: this->copy(); break;
		case InstCode::SIZE: this->size(); break;
		case InstCode::PRINT: this->print(); break;
		case InstCode::SCRAP: this->scrap(); break;
		case InstCode::CLEAR: this->clear(); break;
		case InstCode::FETCH: this->fetch(); break;
		case InstCode::INIT: this->env.memory.push(this->newStackFrame()); break;

		case InstCode::NEWL: this->newl(); break;
		case InstCode::NEWU: this->newu(); break;

		case InstCode::ADDI: this->addi(); break;
		case InstCode::SUBI: this->subi(); break;
		case InstCode::MLTI: this->mlti(); break;
		case InstCode::DIVI: this->divi(); break;
		case InstCode::POWI: this->powi(); break;
		case InstCode::MODI: this->modi(); break;
		case InstCode::CASTI: this->casti(); break;
		case InstCode::INC: this->inc(); break;
		case InstCode::DEC: this->dec(); break;
		
		case InstCode::ADDF: this->addf(); break;
		case InstCode::SUBF: this->subf(); break;
		case InstCode::MLTF: this->mltf(); break;
		case InstCode::DIVF: this->divf(); break;
		case InstCode::POWF: this->powf(); break;
		case InstCode::MODF: this->modf(); break;
		case InstCode::CASTF: this->castf(); break;

		case InstCode::BITOR: this->bit_or(); break;
		case InstCode::BITAND: this->bit_and(); break;
		case InstCode::BITXOR: this->bit_xor(); break;
		
		case InstCode::LOGOR: this->log_or(); break;
		case InstCode::LOGAND: this->log_and(); break;
		case InstCode::LOGXOR: this->log_xor(); break;

		case InstCode::EQLI: this->eqli(); break;
		case InstCode::SMLI: this->smli(); break;
		case InstCode::BGRI: this->bgri(); break;
		case InstCode::SPSHI: this->spshi(); break;

		case InstCode::EQLF: this->eqlf(); break;
		case InstCode::SMLF: this->smlf(); break;
		case InstCode::BGRF: this->bgrf(); break;
		case InstCode::SPSHF: this->spshf(); break;

		case InstCode::CALL: this->call(); break;
		case InstCode::GOTO: this->got0(); break;
		case InstCode::IFSK: this->ifsk(); break;
		case InstCode::RETURN: this->rtrn(); break;

		case InstCode::EXT0: this->extensions[0]->call(this->getArg8()); break;
		case InstCode::EXT1: this->extensions[1]->call(this->getArg8()); break;
		case InstCode::EXT2: this->extensions[2]->call(this->getArg8()); break;
		case InstCode::EXT3: this->extensions[3]->call(this->getArg8()); break;
		case InstCode::EXT4: this->extensions[4]->call(this->getArg8()); break;
		case InstCode::EXT5: this->extensions[5]->call(this->getArg8()); break;
		case InstCode::EXT6: this->extensions[6]->call(this->getArg8()); break;
		case InstCode::EXT7: this->extensions[7]->call(this->getArg8()); break;

		case InstCode::ARRAY: this->array(); break;
		case InstCode::LOOP: this->loop(); break;
		
		default:
			std::string hex;
			std::stringstream ss;
			ss << std::setfill('0') << std::setw(2) << std::hex << int(static_cast<std::uint8_t>(this->opcode));
			ss >> hex;
			throw std::runtime_error("Unknown instruction: 0x" + hex);
		}
		// stack size guard
		if(this->env.acc.isFull()){
			throw std::runtime_error("Stack limit one on acc is reached");
		}
		if(this->env.adr.isFull()){
			throw std::runtime_error("Stack limit one on adr is reached");
		}
	}
}


// memory inst
void ltn::VM::exit(){
	this->env.running = false;
}
// copy value from memory to acc
void ltn::VM::load(){
	std::uint32_t addr = static_cast<std::uint32_t>(this->env.pollU());
	this->env.acc.push(this->env.memory.top()[this->env.resolveAddr(addr)]);
}
// pop value from acc and write to memory
void ltn::VM::store(){
	std::uint32_t addr = static_cast<std::uint32_t>(this->env.pollU());
	this->env.memory.top()[this->env.resolveAddr(addr)] = this->env.pollU();
}

void ltn::VM::copy(){
	this->env.push(this->env.acc.top());
}
void ltn::VM::size(){
	this->env.push(this->env.acc.size());
}
// print or put value into ouput
void ltn::VM::print(){
	switch (this->getArg8()){
	case 0:
		std::cout << this->env.pollI() << std::endl;
		break;
	case 1:
		std::cout << this->env.pollF() << std::endl;
		break;
	default:
		std::cout << this->env.pollU()  << std::endl;
		break;
	}
	
}
// pop and discard one value from acc
void ltn::VM::scrap(){
	this->env.acc.pop();
}
// discard entire accStack
void ltn::VM::clear(){
	this->env.acc.reset();
}
// push args and sysStack into extension as a kind of syscall
void ltn::VM::array(){
	this->arrayExt.call(this->getArg8());
}
void ltn::VM::loop(){
	this->loopExt.call(this->getArg8());
}

// TODO
void ltn::VM::fetch(){
	std::cout << "Fetch" << std::endl;
}

void ltn::VM::casti(){
	this->env.push(static_cast<std::int64_t>(std::round(this->env.pollF())));
}

void ltn::VM::castf(){
	this->env.push(static_cast<double>(this->env.pollI()));
}


// new inst (can be merged with bitxor)
// load a value in the lower 32 bits
void ltn::VM::newl(){
	this->env.acc.push(this->getArg32());
} 
// load a value in the upper 32 bits
void ltn::VM::newu(){
	this->env.acc.push(static_cast<std::uint64_t>(this->getArg32()) << 32);
}


// all math, logic, bitwise and comparison
// instructions are popping the upper 2 values from accStack 
// and pushing the result back onto the accStack

// math inst
void ltn::VM::addi(){
	std::int64_t r = this->env.pollI();
	std::int64_t l = this->env.pollI();
	
	this->env.push(l + r);
}
void ltn::VM::subi(){
	std::int64_t r = this->env.pollI();
	std::int64_t l = this->env.pollI();
	
	this->env.push(l - r);
}
void ltn::VM::mlti(){
	std::int64_t r = this->env.pollI();
	std::int64_t l = this->env.pollI();
	
	this->env.push(l * r);
}
void ltn::VM::divi(){
	std::int64_t r = this->env.pollI();
	std::int64_t l = this->env.pollI();
	
	this->env.push(l / r);
}
void ltn::VM::powi(){
	std::int64_t r = this->env.pollI();
	std::int64_t l = this->env.pollI();
	
	this->env.push(static_cast<std::int64_t>(std::pow(l, r)));
}
void ltn::VM::modi(){
	std::int64_t r = this->env.pollI();
	std::int64_t l = this->env.pollI();
	this->env.push(l % r);
}

void ltn::VM::inc(){
	this->env.acc.top()++;
}
void ltn::VM::dec(){
	this->env.acc.top()--;
}


void ltn::VM::addf(){
	double r = this->env.pollF();
	double l = this->env.pollF();
	this->env.push(l + r);
}
void ltn::VM::subf(){
	double r = this->env.pollF();
	double l = this->env.pollF();
	this->env.push(l - r);
}
void ltn::VM::mltf(){
	double r = this->env.pollF();
	double l = this->env.pollF();
	
	this->env.push(l * r);
}
void ltn::VM::divf(){
	double r = this->env.pollF();
	double l = this->env.pollF();
	
	this->env.push(l / r);
}
void ltn::VM::powf(){
	double r = this->env.pollF();
	double l = this->env.pollF();
	
	this->env.push(std::pow(l,r));
}
void ltn::VM::modf(){
	double r = this->env.pollF();
	double l = this->env.pollF();
	this->env.push(std::fmod(l,r));
}


// bitwise
void ltn::VM::bit_or(){
	std::uint64_t r = this->env.pollU();
	std::uint64_t l = this->env.pollU();
	this->env.push(l | r);
}
void ltn::VM::bit_and(){
	std::uint64_t r = this->env.pollU();
	std::uint64_t l = this->env.pollU();
	this->env.push(l & r);
}
void ltn::VM::bit_xor(){
	std::uint64_t r = this->env.pollU();
	std::uint64_t l = this->env.pollU();
	this->env.push(l ^ r);
}


// logic
void ltn::VM::log_or(){
	std::uint64_t r = this->env.pollU();
	std::uint64_t l = this->env.pollU();
	this->env.push(l || r);
}
void ltn::VM::log_and() {
	std::uint64_t r = this->env.pollU();
	std::uint64_t l = this->env.pollU();
	this->env.push(l && r);
}
void ltn::VM::log_xor() {
	std::uint64_t r = this->env.pollU();
	std::uint64_t l = this->env.pollU();
	this->env.push(!l != !r);
}


// comparison
void ltn::VM::eqli(){
	std::int64_t r = this->env.pollI();
	std::int64_t l = this->env.pollI();
	this->env.push(l == r);
}
void ltn::VM::smli(){
	std::int64_t r = this->env.pollI();
	std::int64_t l = this->env.pollI();
	this->env.push(l < r);
}
void ltn::VM::bgri(){
	std::int64_t r = this->env.pollI();
	std::int64_t l = this->env.pollI();
	this->env.push(l > r);
}
void ltn::VM::spshi(){
	std::int64_t r = this->env.pollI();
	std::int64_t l = this->env.pollI();
	if(l == r) return this->env.push(0L);
	if(l > r) return this->env.push(1L);
	if(l < r) return this->env.push(-1L);
}

void ltn::VM::eqlf(){
	double l = this->env.pollF();
	double r = this->env.pollF();
	this->env.push(l == r);
}
void ltn::VM::smlf(){
	double r = this->env.pollF();
	double l = this->env.pollF();
	this->env.push(l < r);
}
void ltn::VM::bgrf(){
	double r = this->env.pollF();
	double l = this->env.pollF();
	this->env.push(l > r);
}
void ltn::VM::spshf(){
	double r = this->env.pollF();
	double l = this->env.pollF();
	if(l == r) return this->env.push(0L);
	if(l > r) return this->env.push(1L);
	if(l < r) return this->env.push(-1L);
}

// jump and push address to adrStack
void ltn::VM::call(){
	this->env.adr.push(this->env.pc);
	this->env.memory.push(this->newStackFrame());
	this->got0();
}
// jump without pushign the address to adrStack
void ltn::VM::got0(){
	this->env.pc = this->getArg56();
}
// pop last address from adrStack and jump to it 
void ltn::VM::rtrn(){
	this->env.pc = this->env.adr.pop();
	this->env.memory.pop();
}
// skip one instruction if value popped is 0
void ltn::VM::ifsk(){
	if(this->env.pollI() == 0){
		this->env.pc++;
	}
}