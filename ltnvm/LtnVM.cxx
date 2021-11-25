#include "LtnVM.hxx"
#include "ltn/InstructionSet.hxx"
#include <sstream>
#include "Stringify.hxx"
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
			case Inst::ADD: this->add(); break;
			case Inst::SUB: this->sub(); break;
			case Inst::MLT: this->mlt(); break;
			case Inst::DIV: this->div(); break;
			case Inst::MOD: this->mod(); break;

			case Inst::EQL: this->eql(); break;
			case Inst::UEQL: this->ueql(); break;
			case Inst::SML: this->sml(); break;
			case Inst::BGR: this->bgr(); break;
			case Inst::SMLEQL: this->smleql(); break;
			case Inst::BGREQL: this->bgreql(); break;
			case Inst::SHIFT_L: this->shift_l(); break;
			case Inst::SHIFT_R: this->shift_r(); break;
			
			case Inst::NEG: this->neg(); break;
			case Inst::NOT: this->n0t(); break;
			case Inst::INC: this->inc(); break;
			case Inst::DEC: this->dec(); break;

			case Inst::NEWI: this->newi(); break;
			case Inst::NEWF: this->newf(); break;
			case Inst::NEWU: this->newu(); break;
			case Inst::ADDR: this->addr(); break;
			case Inst::TRUE: this->truE(); break;
			case Inst::FALSE: this->falsE(); break;
			case Inst::NEWARR: this->newarr(); break;
			case Inst::NEWSTR: this->newstr(); break;
			case Inst::NEWOUT_STD: this->newout_std(); break;
			case Inst::NEWIN_STD: this->newin_std(); break;
			case Inst::NVLL: this->null(); break;
			case Inst::CHAR: this->ch4r(); break;
			case Inst::ELEM: this->elem(); break;

			case Inst::JUMP: this->jump(); break;
			case Inst::CALL: this->call(); break;
			case Inst::RETURN: this->reTurn(); break;
			case Inst::IF: this->iF(); break;
			case Inst::ERROR: this->error(); break;
			case Inst::EXIT: {
				this->ostream.get() << "Exit main() with return value: ";
				const auto value = this->reg.pop();
				this->ostream.get() << toString(value, this->heap);
				this->ostream.get() << "\n";
				return;
			}
				
			
			case Inst::READ: this->read(); break;
			case Inst::WRITE: this->write(); break;
			case Inst::SCRAP: this->scrap(); break;
			case Inst::MAKEVAR: this->makevar(); break;
			case Inst::AT: this->at(); break;
			case Inst::AT_WRITE: this->at_write(); break;

			case Inst::OUT: this->out(); break;
			case Inst::IN_STR: this->in_str(); break;
			case Inst::IN_LINE: this->in_line(); break;
			case Inst::IN_INT: this->in_int(); break;
			case Inst::IN_FLOAT: this->in_float(); break;

			case Inst::MIN: this->min(); break;
			case Inst::MAX: this->max(); break;
			case Inst::ROUND: this->round(); break;
			case Inst::FLOOR: this->floor(); break;
			case Inst::CEIL: this->ceil(); break;
			case Inst::ABS: this->abs(); break;
			
			case Inst::SIN: this->sin(); break;
			case Inst::COS: this->cos(); break;
			case Inst::TAN: this->tan(); break;
			
			default: {
				std::stringstream ss;
				ss << "Illegal Instruction: " << std::hex << int(inst) << std::dec;
				throw std::runtime_error{ss.str()};
			} break;
			}
		}
	}
}
