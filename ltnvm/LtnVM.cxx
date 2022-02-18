#include "LtnVM.hxx"
#include "ltn/InstructionSet.hxx"
#include <sstream>
#include "cast.hxx"
namespace ltn::vm {

	void LtnVM::registerExternal(
		std::int64_t id,
		std::unique_ptr<ext::External> && ext) {
		this->externals.emplace(id, std::move(ext));
	}

	void LtnVM::error(const std::string & msg) {
		const auto ref = this->heap.alloc<String>({msg});
		this->reg.push(value::string(ref));
		this->thr0w();
	}

	void LtnVM::run() {
		this->reg.reset();
		this->stack.reset();
		this->heap.reset();
		this->pc = 0;
		RESUME:
		try {
			while(true) {
				std::uint8_t inst = this->fetchByte();
				switch (static_cast<Inst>(inst)) {
				case Inst::EXIT: {
					this->ostream.get() << "Exit main() with return value: ";
					const auto value = this->reg.pop();
					this->ostream.get() << cast::to_string(value, this->heap);
					this->ostream.get() << "\n";
					return;
				}
				
				case Inst::ERROR: {
					this->ostream.get() << "Terminated after an error occured \n";
					return;
				}

				case Inst::STATE: this->state(); break;
				case Inst::TRY: this->tRy(); break;
				case Inst::THROW: this->thr0w(); break;
				
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
				case Inst::NEWC: this->newc(); break;
				case Inst::TRUE: this->truE(); break;
				case Inst::FALSE: this->falsE(); break;
				case Inst::NVLL: this->null(); break;

				case Inst::JUMP: this->jump(); break;
				case Inst::CALL: this->call(); break;
				case Inst::RETURN: this->reTurn(); break;
				case Inst::IF: this->iF(); break;
				case Inst::INVOKE: this->invoke(); break;
				case Inst::EXTERNAL: this->external(); break;
				case Inst::ALGORITHM: this->algorithm(); break;
				case Inst::CAPTURE: this->capture(); break;
				case Inst::PARAMETERS: this->parameters(); break;
					
				case Inst::NEWARR: this->newarr(); break;
				case Inst::NEWSTR: this->newstr(); break;
				case Inst::NEWOUT: this->newout(); break;
				case Inst::NEWIN: this->newin(); break;
				case Inst::NEWFX: this->newfx(); break;
				case Inst::NEWCLOCK: this->newclock(); break;
				case Inst::NEWSTRUCT: this->newstruct(); break;
				case Inst::NEWRANGE: this->newrange(); break;
				case Inst::NEWSTACK: this->newstack(); break;
				case Inst::NEWQUEUE: this->newqueue(); break;
				case Inst::NEWMAP: this->newmap(); break;
				
				case Inst::READ: this->read(); break;
				case Inst::WRITE: this->write(); break;
				case Inst::SCRAP: this->scrap(); break;
				case Inst::MAKEVAR: this->makevar(); break;
				case Inst::READ_X: this->read_x(); break;
				case Inst::WRITE_X: this->write_x(); break;
				case Inst::SWAP: this->swap(); break;

				case Inst::READ_0: this->read_0(); break;
				case Inst::READ_1: this->read_1(); break;
				case Inst::READ_2: this->read_2(); break;
				case Inst::READ_3: this->read_3(); break;
				case Inst::WRITE_0: this->write_0(); break;
				case Inst::WRITE_1: this->write_1(); break;
				case Inst::WRITE_2: this->write_2(); break;
				case Inst::WRITE_3: this->write_3(); break;

				case Inst::OUT: this->out(); break;
				case Inst::IN_STR: this->in_str(); break;
				case Inst::IN_LINE: this->in_line(); break;
				case Inst::IN_INT: this->in_int(); break;
				case Inst::IN_FLOAT: this->in_float(); break;
				case Inst::IS_EOF: this->is_eof(); break;

				case Inst::MIN: this->min(); break;
				case Inst::MAX: this->max(); break;
				case Inst::ROUND: this->round(); break;
				case Inst::FLOOR: this->floor(); break;
				case Inst::CEIL: this->ceil(); break;
				case Inst::ABS: this->abs(); break;
				case Inst::HYPOT: this->hypot(); break;
				case Inst::SQRT: this->sqrt(); break;
				case Inst::LOG: this->log(); break;
				case Inst::LN: this->ln(); break;
				case Inst::POW: this->pow(); break;
				
				case Inst::SIN: this->sin(); break;
				case Inst::COS: this->cos(); break;
				case Inst::TAN: this->tan(); break;
				
				case Inst::SIZE: this->size(); break;
				case Inst::AT: this->at(); break;
				case Inst::AT_WRITE: this->at_write(); break;
				case Inst::FRONT: this->front(); break;
				case Inst::BACK: this->back(); break;
				case Inst::INSERT: this->insert(); break;
				case Inst::REMOVE: this->remove(); break;
				case Inst::BEGIN: this->begin(); break;
				case Inst::END: this->end(); break;
				case Inst::PUSH: this->push(); break;
				case Inst::POP: this->pop(); break;
				case Inst::PEEK: this->peek(); break;
				case Inst::CONTAINS: this->contains(); break;

				case Inst::CAST_BOOL: this->cast_bool(); break;
				case Inst::CAST_CHAR: this->cast_char(); break;
				case Inst::CAST_INT: this->cast_int(); break;
				case Inst::CAST_FLOAT: this->cast_float(); break;
				case Inst::CAST_STRING: this->cast_string(); break;
				case Inst::CAST_ARRAY: this->cast_array(); break;

				case Inst::TYPEID: this->typeId(); break;
				case Inst::CLONE: this->clone(); break;

				case Inst::MEMBER_READ: this->member_read(); break;
				case Inst::MEMBER_WRITE: this->member_write(); break;


				default: {
					std::stringstream ss;
					ss << "Illegal Instruction: " << std::hex << int(inst) << std::dec;
					throw std::runtime_error{ss.str()};
				} break;				
				}
			}
		}
		catch(const Exception & error) {
			this->error(error.msg);
			goto RESUME;
		}
	}
}
