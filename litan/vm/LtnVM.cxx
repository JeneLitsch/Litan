#include "LtnVM.hxx"
#include <iostream>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "LtnAccessViolation.hxx"
#include "LtnPointerAccessViolation.hxx"
#include "LtnIndexAccessViolation.hxx"
#include "LtnIllegalInstruction.hxx"
#include "LtnPopFromEmpty.hxx"

// memorySize and stackLimit in 64bit blocks
ltn::VM::VM() {}

void ltn::VM::installExtension(IExtension & ext, Slot slot){
	this->extensions[static_cast<unsigned>(slot)] = &ext;
	ext.setEnvironsment(this->env);
}


void ltn::VM::init(const std::vector<std::uint64_t> & byteCode){
	this->env.instructions = byteCode;
}

void ltn::VM::run(){
	this->env.acc.reset();
	this->env.heap.clear();
	this->env.stack.clear();
	this->env.pc = 0;
	this->env.loops = {};

	this->execute();
}



void ltn::VM::execute(){
	while(true){
		std::uint64_t inst = this->env.instructions[this->env.pc];
		this->env.pc++;
		InstCode opcode = static_cast<InstCode>(std::uint8_t((inst) & 0xff));
		this->currentInstruction = inst;


		switch (opcode) {
		case InstCode::EXIT: return;
		case InstCode::ERROR: throw Error();
		
		case InstCode::LOAD: this->load(); break;
		case InstCode::STORE: this->store(); break;
		case InstCode::COPY: this->copy(); break;
		case InstCode::SIZE: this->size(); break;
		case InstCode::PRINT: this->print(); break;
		case InstCode::SCRAP: this->scrap(); break;
		case InstCode::CLEAR: this->clear(); break;
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
		case InstCode::MINI: this->mini(); break;
		case InstCode::MAXI: this->maxi(); break;
		
		case InstCode::ADDF: this->addf(); break;
		case InstCode::SUBF: this->subf(); break;
		case InstCode::MLTF: this->mltf(); break;
		case InstCode::DIVF: this->divf(); break;
		case InstCode::POWF: this->powf(); break;
		case InstCode::MODF: this->modf(); break;
		case InstCode::CASTF: this->castf(); break;
		case InstCode::MNSF: this->mnsf(); break;
		case InstCode::MINF: this->minf(); break;
		case InstCode::MAXF: this->maxf(); break;

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
		case InstCode::HEAP_EXIST: this->heapExist(); break;
		case InstCode::HEAP_COPY: this->heapCopy(); break;

		case InstCode::ARRAY_NEW: this->arrayNew(); break;
		case InstCode::ARRAY_CLR: this->arrayClr(); break;
		case InstCode::ARRAY_GET: this->arrayGet(); break;
		case InstCode::ARRAY_SET: this->arraySet(); break;
		case InstCode::ARRAY_LEN: this->arrayLen(); break;
		case InstCode::ARRAY_FLL: this->arrayFll(); break;
		case InstCode::ARRAY_RSZ: this->arrayRsz(); break;
		case InstCode::ARRAY_ERS: this->arrayErs(); break;
		case InstCode::ARRAY_INS: this->arrayIns(); break;
		case InstCode::ARRAY_PUSHF: this->arrayPushF(); break;
		case InstCode::ARRAY_PUSHB: this->arrayPushB(); break;
		case InstCode::ARRAY_POPF: this->arrayPopF(); break;
		case InstCode::ARRAY_POPB: this->arrayPopB(); break;
		case InstCode::ARRAY_GETF: this->arrayGetF(); break;
		case InstCode::ARRAY_GETB: this->arrayGetB(); break;

		case InstCode::STACK_NEW: this->stackNew(); break;
		case InstCode::STACK_PUSH: this->stackPush(); break;
		case InstCode::STACK_POP: this->stackPop(); break;
		case InstCode::STACK_TOP: this->stackTop(); break;
		case InstCode::STACK_SIZE: this->stackSize(); break;
		case InstCode::STACK_EMPTY: this->stackEmpty(); break;
		case InstCode::STACk_CLEAR: this->stackClear(); break;

		case InstCode::QUEUE_NEW: this->queueNew(); break;
		case InstCode::QUEUE_PUSH: this->queuePush(); break;
		case InstCode::QUEUE_POP: this->queuePop(); break;
		case InstCode::QUEUE_FRONT: this->queueFront(); break;
		case InstCode::QUEUE_SIZE: this->queueSize(); break;
		case InstCode::QUEUE_EMPTY: this->queueEmpty(); break;
		case InstCode::QUEUE_CLEAR: this->queueClear(); break;

		case InstCode::DEQUE_NEW: this->dequeNew(); break;
		case InstCode::DEQUE_PUSHF: this->dequePushF(); break;
		case InstCode::DEQUE_PUSHB: this->dequePushB(); break;
		case InstCode::DEQUE_POPF: this->dequePopF(); break;
		case InstCode::DEQUE_POPB: this->dequePopB(); break;
		case InstCode::DEQUE_FRONT: this->dequeFront(); break;
		case InstCode::DEQUE_BACK: this->dequeBack(); break;
		case InstCode::DEQUE_SIZE: this->dequeSize(); break;
		case InstCode::DEQUE_EMPTY: this->dequeEmpty(); break;
		case InstCode::DEQUE_CLEAR: this->dequeClear(); break;

		case InstCode::LOOP_RANGE: this->loopRange(); break;
		case InstCode::LOOP_INF: this->loopInf(); break;
		case InstCode::LOOP_STOP: this->loopStop(); break;
		case InstCode::LOOP_CONT: this->loopCont(); break;
		case InstCode::LOOP_IDX: this->loopIdx(); break;

		case InstCode::STRING_NEW: this->stringNew(); break;
		case InstCode::STRING_ADD: this->stringAdd(); break;
		case InstCode::STRING_DATA: this->stringData(); break;
		case InstCode::STRING_PRINT: this->stringPrint(); break;
		
		default: throw IllegalInstruction(static_cast<std::uint8_t>(opcode));
		}
	}
}

