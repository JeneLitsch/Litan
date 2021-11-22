#include "LtnVM.hxx"
#include "ltn/InstructionSet.hxx"
#include <sstream>
namespace ltn::vm {
	std::uint8_t LtnVM::fetchByte() {
		return byteCode[this->pc++];
	}

	std::uint64_t LtnVM::fetchUint() {
		std::uint64_t value = 0;
		for(auto i = 0; i < 8; i++) {
			value <<= 8;
			value |= static_cast<std::uint64_t>(this->fetchByte());
		}
		return value;
	}


	void LtnVM::exec() {
		while(true) {
			std::uint8_t inst = this->fetchByte();
			// ostream.get() << this->pc-1 << " : " << std::hex << "0x" << int(inst) << "\n" << std::dec; 
			switch (static_cast<Inst>(inst))
			{
			case Inst::ADD: add(); break;
			case Inst::SUB: sub(); break;
			case Inst::MLT: mlt(); break;
			case Inst::DIV: div(); break;
			case Inst::MOD: mod(); break;

			case Inst::EQL: eql(); break;
			case Inst::UEQL: ueql(); break;
			case Inst::SML: sml(); break;
			case Inst::BGR: bgr(); break;
			case Inst::SMLEQL: smleql(); break;
			case Inst::BGREQL: bgreql(); break;
			
			case Inst::NEG: neg(); break;
			case Inst::NOT: n0t(); break;
			case Inst::INC: inc(); break;
			case Inst::DEC: dec(); break;

			case Inst::NEWI: newi(); break;
			case Inst::NEWF: newf(); break;
			case Inst::NEWU: newu(); break;
			case Inst::ADDR: addr(); break;
			case Inst::TRUE: truE(); break;
			case Inst::FALSE: falsE(); break;
			case Inst::NEWARR: newarr(); break;
			case Inst::NEWSTR: newstr(); break;
			case Inst::NVLL: null(); break;
			case Inst::CHAR: ch4r(); break;
			case Inst::ELEM: elem(); break;

			case Inst::JUMP: jump(); break;
			case Inst::CALL: call(); break;
			case Inst::RETURN: reTurn(); break;
			case Inst::IF: iF(); break;
			case Inst::ERROR: error(); break;
			case Inst::EXIT: {
				this->ostream.get() << "Exit main() with return value: ";
				this->out();
				this->ostream.get() << "\n";
				return;
			}
				
			
			case Inst::READ: read(); break;
			case Inst::WRITE: write(); break;
			case Inst::SCRAP: scrap(); break;
			case Inst::MAKEVAR: makevar(); break;

			case Inst::OUT: out(); break;

			case Inst::AT: at(); break;
			case Inst::AT_WRITE: at_write(); break;
			
			default: {
				std::stringstream ss;
				ss << "Illegal Instruction: " << std::hex << int(inst) << std::dec;
				throw std::runtime_error{ss.str()};
			} break;
			}
		}
	}
}
