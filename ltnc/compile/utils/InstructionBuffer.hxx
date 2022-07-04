#pragma once
#include "ltn/InstructionSet.hxx"
#include "stdxx/array.hxx"

namespace ltn::c {
	class InstructionBuffer {
	public:
		InstructionBuffer & operator<<(const InstructionBuffer & buf) {
			this->array += buf.get();
			return *this;
		}

		InstructionBuffer & operator<<(const std::span<const ltn::inst::Instruction> buf) {
			this->array += buf;
			return *this;
		}

		InstructionBuffer & operator<<(const ltn::inst::Instruction & inst) {
			this->array += inst;
			return *this;
		}

		const std::vector<ltn::inst::Instruction> & get() const {
			return array;
		}

		void clear() {
			this->array.clear();
		}
	private:
		std::vector<ltn::inst::Instruction> array;
	};
}