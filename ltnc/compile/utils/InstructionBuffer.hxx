#pragma once
#include "ltnc/inst/inst.hxx"
#include "stdxx/array.hxx"

namespace ltn::c {
	class InstructionBuffer {
	public:
		InstructionBuffer(std::vector<inst::Inst> array  = {})
		: array{array} {};

		InstructionBuffer(std::initializer_list<inst::Inst> array)
		: array{array} {};

		InstructionBuffer & operator<<(const InstructionBuffer & buf) {
			this->array += buf.get();
			return *this;
		}

		InstructionBuffer & operator<<(const std::span<const inst::Inst> buf) {
			this->array += buf;
			return *this;
		}

		InstructionBuffer & operator<<(const inst::Inst & inst) {
			this->array += inst;
			return *this;
		}

		const std::vector<inst::Inst> & get() const {
			return array;
		}

		void clear() {
			this->array.clear();
		}
	private:
		std::vector<inst::Inst> array;
	};
}