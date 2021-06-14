#include "VM.hxx"
#include <iostream>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <iomanip>

// memorySize and stackLimit in 64bit blocks
ltn::VM::VM() {
	
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

void ltn::VM::reset(){
	this->env.acc.reset();
	this->env.heap.clear();
	this->env.stack.clear();
	this->env.pc = 0;
	this->env.loops = {};
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
		case InstCode::INIT: this->init(); break;
		case InstCode::STACKALLOC: this->stackalloc(); break;

		case InstCode::NEWL: this->newl(); break;
		case InstCode::NEWU: this->newu(); break;

		case InstCode::ADDI: this->addi(); break;
		case InstCode::SUBI: this->subi(); break;
		case InstCode::MLTI: this->mlti(); break;
		case InstCode::DIVI: this->divi(); break;
		case InstCode::POWI: this->powi(); break;
		case InstCode::MODI: this->modi(); break;
		case InstCode::CASTI: this->casti(); break;
		case InstCode::INCI: this->inci(); break;
		case InstCode::DECI: this->deci(); break;
		case InstCode::MNSI: this->mnsi(); break;
		
		case InstCode::ADDF: this->addf(); break;
		case InstCode::SUBF: this->subf(); break;
		case InstCode::MLTF: this->mltf(); break;
		case InstCode::DIVF: this->divf(); break;
		case InstCode::POWF: this->powf(); break;
		case InstCode::MODF: this->modf(); break;
		case InstCode::CASTF: this->castf(); break;
		case InstCode::MNSF: this->mnsf(); break;

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

		case InstCode::HEAP_DEL: this->heapDel(); break;

		case InstCode::ARRAY_NEW: this->arrayNew(); break;
		case InstCode::ARRAY_CLR: this->arrayClr(); break;
		case InstCode::ARRAY_GET: this->arrayGet(); break;
		case InstCode::ARRAY_SET: this->arraySet(); break;
		case InstCode::ARRAY_ADD: this->arrayAdd(); break;
		case InstCode::ARRAY_POP: this->arrayPop(); break;
		case InstCode::ARRAY_LEN: this->arrayLen(); break;
		case InstCode::ARRAY_FLL: this->arrayFll(); break;
		case InstCode::ARRAY_RSZ: this->arrayRsz(); break;
		case InstCode::ARRAY_ERS: this->arrayErs(); break;

		case InstCode::LOOP_RANGE: this->loopRange(); break;
		case InstCode::LOOP_INF: this->loopInf(); break;
		case InstCode::LOOP_STOP: this->loopStop(); break;
		case InstCode::LOOP_CONT: this->loopCont(); break;
		case InstCode::LOOP_IDX: this->loopIdx(); break;

		case InstCode::STRING_NEW: this->stringNew(); break;
		case InstCode::STRING_ADD: this->stringAdd(); break;
		case InstCode::STRING_DATA: this->stringData(); break;
		case InstCode::STRING_PRINT: this->stringPrint(); break;
		default:
			std::string hex;
			std::stringstream ss;
			ss << std::setfill('0') << std::setw(2) << std::hex << int(static_cast<std::uint8_t>(this->opcode));
			ss >> hex;
			throw std::runtime_error("Unknown instruction: 0x" + hex);
		}
		// std::cout << "Size: " << this->env.acc.size() << " Inst: " << int(this->opcode) << std::endl;
		// stack size guard
		if(this->env.acc.isFull()){
			throw std::runtime_error("Stack limit one on acc is reached");
		}
	}
}


// copy value from memory to acc
void ltn::VM::load(){
	std::uint32_t addr = static_cast<std::uint32_t>(this->env.acc.popU());
	this->env.acc.push(this->env.stack.get().memoryBlock[addr]);
}
// pop value from acc and write to memory
void ltn::VM::store(){
	std::uint32_t addr = static_cast<std::uint32_t>(this->env.acc.popU());
	this->env.stack.get().memoryBlock[addr] = this->env.acc.popU();
}

void ltn::VM::copy(){
	this->env.acc.push(this->env.acc.top());
}
void ltn::VM::size(){
	this->env.acc.push(this->env.acc.size());
}
// print or put value into ouput
void ltn::VM::print(){
	switch (this->getArg8()){
	case 0:
		std::cout << this->env.acc.popI() << std::endl;
		break;
	case 1:
		std::cout << this->env.acc.popF() << std::endl;
		break;
	default:
		std::cout << this->env.acc.popU()  << std::endl;
		break;
	}
	
}
// pop and discard one value from acc
void ltn::VM::scrap(){
	this->env.acc.popU();
}
// discard entire accStack
void ltn::VM::clear(){
	this->env.acc.reset();
}

// TODO
void ltn::VM::fetch(){
	std::cout << "Fetch" << std::endl;
}

void ltn::VM::init() {
	this->env.stack.push(0); 
}
void ltn::VM::stackalloc() {
	this->env.stack.get().memoryBlock.resize(this->env.stack.get().memoryBlock.size() + this->getArg32());
}

void ltn::VM::casti(){
	this->env.acc.push(static_cast<std::int64_t>(std::round(this->env.acc.popF())));
}

void ltn::VM::castf(){
	this->env.acc.push(static_cast<double>(this->env.acc.popI()));
}


// new inst (can be merged with bitxor)
// load a value in the lower 32 bits
void ltn::VM::newl(){
	this->env.acc.push(static_cast<std::uint64_t>(this->getArg32()));
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
	std::int64_t r = this->env.acc.popI();
	std::int64_t l = this->env.acc.popI();
	
	this->env.acc.push(l + r);
}
void ltn::VM::subi(){
	std::int64_t r = this->env.acc.popI();
	std::int64_t l = this->env.acc.popI();
	
	this->env.acc.push(l - r);
}
void ltn::VM::mlti(){
	std::int64_t r = this->env.acc.popI();
	std::int64_t l = this->env.acc.popI();
	
	this->env.acc.push(l * r);
}
void ltn::VM::divi(){
	std::int64_t r = this->env.acc.popI();
	std::int64_t l = this->env.acc.popI();
	
	this->env.acc.push(l / r);
}
void ltn::VM::powi(){
	std::int64_t r = this->env.acc.popI();
	std::int64_t l = this->env.acc.popI();
	
	this->env.acc.push(static_cast<std::int64_t>(std::pow(l, r)));
}
void ltn::VM::modi(){
	std::int64_t r = this->env.acc.popI();
	std::int64_t l = this->env.acc.popI();
	this->env.acc.push(l % r);
}

void ltn::VM::inci(){
	this->env.acc.top()++;
}
void ltn::VM::deci(){
	this->env.acc.top()--;
}

void ltn::VM::mnsi(){
	this->env.acc.push(-this->env.acc.popI());
}

void ltn::VM::addf(){
	double r = this->env.acc.popF();
	double l = this->env.acc.popF();
	this->env.acc.push(l + r);
}
void ltn::VM::subf(){
	double r = this->env.acc.popF();
	double l = this->env.acc.popF();
	this->env.acc.push(l - r);
}
void ltn::VM::mltf(){
	double r = this->env.acc.popF();
	double l = this->env.acc.popF();
	
	this->env.acc.push(l * r);
}
void ltn::VM::divf(){
	double r = this->env.acc.popF();
	double l = this->env.acc.popF();
	
	this->env.acc.push(l / r);
}
void ltn::VM::powf(){
	double r = this->env.acc.popF();
	double l = this->env.acc.popF();
	
	this->env.acc.push(std::pow(l,r));
}
void ltn::VM::modf(){
	double r = this->env.acc.popF();
	double l = this->env.acc.popF();
	this->env.acc.push(std::fmod(l,r));
}

void ltn::VM::mnsf(){
	this->env.acc.push(-this->env.acc.popF());
}

// bitwise
void ltn::VM::bit_or(){
	std::uint64_t r = this->env.acc.popU();
	std::uint64_t l = this->env.acc.popU();
	this->env.acc.push(l | r);
}
void ltn::VM::bit_and(){
	std::uint64_t r = this->env.acc.popU();
	std::uint64_t l = this->env.acc.popU();
	this->env.acc.push(l & r);
}
void ltn::VM::bit_xor(){
	std::uint64_t r = this->env.acc.popU();
	std::uint64_t l = this->env.acc.popU();
	this->env.acc.push(l ^ r);
}


// logic
void ltn::VM::log_or(){
	std::uint64_t r = this->env.acc.popU();
	std::uint64_t l = this->env.acc.popU();
	this->env.acc.push(l || r);
}
void ltn::VM::log_and() {
	std::uint64_t r = this->env.acc.popU();
	std::uint64_t l = this->env.acc.popU();
	this->env.acc.push(l && r);
}
void ltn::VM::log_xor() {
	std::uint64_t r = this->env.acc.popU();
	std::uint64_t l = this->env.acc.popU();
	this->env.acc.push(!l != !r);
}


// comparison
void ltn::VM::eqli(){
	std::int64_t r = this->env.acc.popI();
	std::int64_t l = this->env.acc.popI();
	this->env.acc.push(l == r);
}
void ltn::VM::smli(){
	std::int64_t r = this->env.acc.popI();
	std::int64_t l = this->env.acc.popI();
	this->env.acc.push(l < r);
}
void ltn::VM::bgri(){
	std::int64_t r = this->env.acc.popI();
	std::int64_t l = this->env.acc.popI();
	this->env.acc.push(l > r);
}
void ltn::VM::spshi(){
	std::int64_t r = this->env.acc.popI();
	std::int64_t l = this->env.acc.popI();
	if(l == r) return this->env.acc.push(0L);
	if(l > r) return this->env.acc.push(1L);
	if(l < r) return this->env.acc.push(-1L);
}

void ltn::VM::eqlf(){
	double l = this->env.acc.popF();
	double r = this->env.acc.popF();
	this->env.acc.push(l == r);
}
void ltn::VM::smlf(){
	double r = this->env.acc.popF();
	double l = this->env.acc.popF();
	this->env.acc.push(l < r);
}
void ltn::VM::bgrf(){
	double r = this->env.acc.popF();
	double l = this->env.acc.popF();
	this->env.acc.push(l > r);
}
void ltn::VM::spshf(){
	double r = this->env.acc.popF();
	double l = this->env.acc.popF();
	if(l == r) return this->env.acc.push(0L);
	if(l > r) return this->env.acc.push(1L);
	if(l < r) return this->env.acc.push(-1L);
}

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

// Heap instructions
void ltn::VM::heapDel(){
	std::uint64_t ptr = this->env.acc.popU();
	this->env.heap.destroy(ptr);
}


// Array instructions
void ltn::VM::arrayNew(){
	this->env.acc.push(this->env.heap.allocateArray());
}


void ltn::VM::arrayClr(){
	std::uint64_t ptr = this->env.acc.popU();
	this->env.heap.accessArray(ptr).clear();
}

void ltn::VM::arrayGet(){
	std::uint64_t idx = this->env.acc.popU();
	std::uint64_t ptr = this->env.acc.popU();
	auto & array = this->env.heap.accessArray(ptr);
	if(idx < array.size()){
		this->env.acc.push(array[idx]);
	}
	else{
		throw std::runtime_error("Access Violation" 
			"at id: " + std::to_string(ptr) + " "
			"at index: " + std::to_string(idx));
	}
}

void ltn::VM::arraySet(){
	std::uint64_t value = this->env.acc.popU();
	std::uint64_t idx = this->env.acc.popU();
	std::uint64_t ptr = this->env.acc.popU();
	auto & array = this->env.heap.accessArray(ptr);
	if(idx < array.size()){
		array[idx] = value;
	}
	else{
		throw std::runtime_error("Access Violation" 
			"at id: " + std::to_string(ptr) + " "
			"at index: " + std::to_string(idx));
	}
}

void ltn::VM::arrayAdd(){
	std::uint64_t value = this->env.acc.popU();
	std::uint64_t ptr = this->env.acc.popU();
	this->env.heap.accessArray(ptr).push_back(value);
}

void ltn::VM::arrayPop(){
	std::uint64_t ptr = this->env.acc.popU();
	auto & array = this->env.heap.accessArray(ptr);
	if(array.empty()) {
		throw std::runtime_error("Access Violation at id: " + std::to_string(ptr) + " attempt to pop from empty buffer");
	}
	this->env.acc.push(array.back());
	array.pop_back();
}

void ltn::VM::arrayLen(){
	std::uint64_t ptr = this->env.acc.popU();
	this->env.acc.push(this->env.heap.accessArray(ptr).size());
}


void ltn::VM::arrayFll() {
	std::uint64_t value = this->env.acc.popU();
	std::uint64_t ptr = this->env.acc.popU();
	std::vector<std::uint64_t> & array = this->env.heap.accessArray(ptr);
	std::fill(array.begin(), array.end(), value);
}

void ltn::VM::arrayRsz(){
	std::uint64_t size = this->env.acc.popU();
	std::uint64_t ptr = this->env.acc.popU();
	this->env.heap.accessArray(ptr).resize(size, 0);
}

void ltn::VM::arrayErs(){
	std::uint64_t idx = this->env.acc.popU();
	std::uint64_t ptr = this->env.acc.popU();
	std::vector<std::uint64_t> & array = this->env.heap.accessArray(ptr);
	array.erase(array.begin() + idx);
}

void ltn::VM::stringNew() {
	this->env.acc.push(this->env.heap.allocateString());
}

void ltn::VM::stringAdd() {
	std::uint64_t ptr2 = this->env.acc.popU();	
	std::uint64_t ptr1 = this->env.acc.popU();
	std::uint64_t ptr3 = this->env.heap.allocateString();
	this->env.heap.accessString(ptr3) = this->env.heap.accessString(ptr1) + this->env.heap.accessString(ptr2);
	this->env.acc.push(ptr3);
}

void ltn::VM::stringData() {
	std::uint64_t ptr = this->env.acc.top();
	std::uint8_t len = this->getArg8();
	std::string str = "";
	for(unsigned int i = 2; i < 2 + len; i++) {
		char chr = static_cast<char>((this->currentInstruction >> i*8) & 0xff);
		str.push_back(chr);
	}
	this->env.heap.accessString(ptr) += str;
}

void ltn::VM::stringPrint() {
	std::uint64_t ptr = this->env.acc.popU();
	std::cout << this->env.heap.accessString(ptr) << std::endl;
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


