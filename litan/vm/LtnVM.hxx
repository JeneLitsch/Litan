#pragma once
#include <cstdint>
#include <stack>
#include <vector>
#include "LtnFloat.hxx"
#include "LtnInstructions.hxx"
#include "LtnIExtension.hxx"
#include "LtnEnvironment.hxx"
#include "LtnError.hxx"

namespace ltn {
	// the i prefix means integer
	// the f prefix means floating point
	// each value and instruction is 64 bit
	// 64bit values are loaded from 2x 32bit literals
	class VM {
	public:
		VM();
		void init(const std::vector<std::uint64_t> & byteCode);
		void run();
		void installExtension(IExtension & ext, Slot slot);

	private:
		Environment env;
		std::array<IExtension*, 8> extensions;
		
		// decoding and args
		std::uint64_t currentInstruction;

		inline std::uint8_t getArg8() { return std::uint8_t((this->currentInstruction >> 8) & 0xff); }
		inline std::uint16_t getArg16() { return std::uint16_t((this->currentInstruction >> 16) & 0xffff); }
		inline std::uint32_t getArg32() { return std::uint32_t((this->currentInstruction >> 32) & 0xffffffff); }
		inline std::uint64_t getArg56() { return std::uint64_t((this->currentInstruction >> 8) & 0xfffffffffffffff); }

		void execute();

		// memory and system instructions
		void load();
		void store();
		void copy();
		void size();
		void print();
		void scrap();
		void clear();
		void init();
		void stackalloc();

		// value instruction
		void casti();
		void castf();
		void newl();
		void newu();

		// int math instructions
		void addi();
		void subi();
		void mlti();
		void divi();
		void powi();
		void modi();
		void inci();
		void deci();
		void mnsi();
		void mini();
		void maxi();
		
		// float math instructions
		void addf();
		void subf();
		void mltf();
		void divf();
		void powf();
		void modf();
		void incf();
		void decf();
		void mnsf();
		void minf();
		void maxf();

		// bitwise instructions
		void bit_or(); 
		void bit_and();
		void bit_xor();
		
		// logic instructions
		void log_or();
		void log_and();
		void log_xor();
		
		// int comparison
		void eqli();
		void smli();
		void bgri();
		void spshi();
		
		// float comparison
		void eqlf();
		void smlf();
		void bgrf();
		void spshf();

		// control flow
		void call();
		void got0();
		void rtrn();
		void ifsk();
		
		// heap
		void heapAllocate();
		void heapDelete();
		void heapExist();
		void heapIsType();
		void heapCopy();
		
		// array 
		void arrayClear();
		void arrayGet();
		void arraySet();
		void arraySize();
		void arrayEmpty();
		void arrayFill();
		void arrayResize();
		void arrayErase();
		void arrayInsert();
		void arrayPushBack();
		void arrayPopBack();
		void arrayFront();
		void arrayBack(); 

		// string instructions
		void stringAdd();
		void stringData();

		// stack(type) instructions
		void stackPush();
		void stackPop();
		void stackTop();
		void stackEmpty();
		void stackSize();
		void stackClear();

		// queue(type) instructions
		void queuePush();
		void queuePop();
		void queueFront();
		void queueEmpty();
		void queueSize();
		void queueClear();

		// queue(type) instructions
		void dequeNew();
		void dequePushF();
		void dequePushB();
		void dequePopF();
		void dequePopB();
		void dequeFront();
		void dequeBack();
		void dequeEmpty();
		void dequeSize();
		void dequeClear();

		// loop instruction
		void loopRange();
		void loopInf();
		void loopCont();
		void loopStop();
		void loopIdx();
	};
}