#pragma once
#include <cstdint>
#include <stack>
#include <vector>
#include "LtnFloat.hxx"
#include "LtnInstructions.hxx"
#include "IExtension.hxx"
#include "LtnEnvironment.hxx"

namespace ltn {
	// the i prefix means integer
	// the f prefix means floating point
	// each value and instruction is 64 bit
	// 64bit values are loaded from 2x 32bit literals
	class VM {
	public:
		enum class Status {
			SUSPENDED,
			EXITED,
			ERROR
		};
		VM();
		void init(const std::vector<std::uint64_t> & byteCode);
		void reset();
		Status run();
		void installExtension(IExtension & ext, Slot slot);

	private:
		Environment env;
		std::array<IExtension*, 8> extensions;

		// decoding and args
		void decode();
		InstCode opcode;
		std::uint64_t currentInstruction;

		inline std::uint8_t getArg8() { return std::uint8_t((this->currentInstruction >> 8) & 0xff); }
		inline std::uint16_t getArg16() { return std::uint16_t((this->currentInstruction >> 16) & 0xffff); }
		inline std::uint32_t getArg32() { return std::uint32_t((this->currentInstruction >> 32) & 0xffffffff); }
		inline std::uint64_t getArg56() { return std::uint64_t((this->currentInstruction >> 8) & 0xfffffffffffffff); }

		Status execute();


		// memory and system instructions
		void load(); void store(); void copy(); void size();
		void print();
		void scrap(); void clear();
		void fetch();
		void init();
		void stackalloc();

		void casti(); void castf();

		// create values
		void newl(); void newu();

		// math instructions
		void addi(); void subi(); void mlti(); void divi(); void powi(); void modi();
		void inci(); void deci();
		void mnsi(); 
		
		void addf(); void subf(); void mltf(); void divf(); void powf(); void modf();
		void incf(); void decf();
		void mnsf();


		// logic and bitwise instructions
		void bit_or(); void bit_and(); void bit_xor();
		void log_or(); void log_and(); void log_xor();
		
		// comparison
		void eqli(); void smli(); void bgri(); void spshi();
		void eqlf(); void smlf(); void bgrf(); void spshf();

		// control flow
		void call();
		void got0();
		void rtrn();
		void ifsk();
		
		// heap
		void heapDel();
		
		// array 
		void arrayNew(); // new array
		void arrayClr(); // clear array
		void arrayGet(); // get element
		void arraySet(); // set element
		void arrayAdd(); // push element
		void arrayPop(); // pop element
		void arrayLen(); // array.size()
		void arrayFll(); // array fill
		void arrayRsz(); // array resize
		void arrayErs(); // erase element

		// string
		void stringNew();
		void stringAdd();
		void stringData();
		void stringPrint();

		// loop
		void loopRange();
		void loopInf();
		void loopCont();
		void loopStop();
		void loopIdx();

		

	};
}