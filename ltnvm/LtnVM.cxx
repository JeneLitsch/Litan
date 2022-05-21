#include "LtnVM.hxx"
#include "ltn/InstructionSet.hxx"
#include <sstream>
#include "cast.hxx"
#include "instructions.hxx"

namespace ltn::vm {

	void LtnVM::register_external(
		std::int64_t id,
		std::unique_ptr<ext::External> && ext) {
		this->core.externals.emplace(id, std::move(ext));
	}

	void LtnVM::error(const std::string & msg) {
		const auto ref = this->core.heap.alloc<String>({msg});
		this->core.reg.push(value::string(ref));
		inst::thr0w(core);
	}

	Value LtnVM::run(const std::vector<std::string> & args) {
		this->core.reg.reset();
		this->core.stack.reset();
		this->core.heap.reset();
		this->core.pc = 0;
		
		// load args
		const auto ref = this->core.heap.alloc<Array>(Array{});
		this->core.reg.push(value::array(ref));
		for(const auto & arg : args) {
			const auto str = this->core.heap.alloc<String>(String{arg});
			auto & arr = this->core.heap.read<Array>(ref).get();
			arr.push_back(value::string(str));
		}

		RESUME:
		try {
			while(true) {
				std::uint8_t inst = this->core.fetch_byte();
				switch (static_cast<Inst>(inst)) {
				case Inst::EXIT: {
					return this->core.reg.pop();

				}
				
				case Inst::ERROR: {
					return value::null;
				}

				case Inst::STATE: inst::state(core); break;
				case Inst::TRY: inst::tRy(core); break;
				case Inst::THROW: inst::thr0w(core); break;
				
				case Inst::ADD: inst::add(core); break;
				case Inst::SUB: inst::sub(core); break;
				case Inst::MLT: inst::mlt(core); break;
				case Inst::DIV: inst::div(core); break;
				case Inst::MOD: inst::mod(core); break;

				case Inst::EQL: inst::eql(core); break;
				case Inst::UEQL: inst::ueql(core); break;
				case Inst::SML: inst::sml(core); break;
				case Inst::BGR: inst::bgr(core); break;
				case Inst::SMLEQL: inst::smleql(core); break;
				case Inst::BGREQL: inst::bgreql(core); break;
				case Inst::SHIFT_L: inst::shift_l(core); break;
				case Inst::SHIFT_R: inst::shift_r(core); break;
				
				case Inst::NEG: inst::neg(core); break;
				case Inst::NOT: inst::n0t(core); break;
				case Inst::INC: inst::inc(core); break;
				case Inst::DEC: inst::dec(core); break;
				
				case Inst::COMP: inst::comp(core); break;
				case Inst::APPROX: inst::approx(core); break;
				case Inst::BETWEEN: inst::between(core); break;

				case Inst::NEWI: inst::newi(core); break;
				case Inst::NEWF: inst::newf(core); break;
				case Inst::NEWU: inst::newu(core); break;
				case Inst::NEWC: inst::newc(core); break;
				case Inst::TRUE: inst::truE(core); break;
				case Inst::FALSE: inst::falsE(core); break;
				case Inst::NVLL: inst::null(core); break;

				case Inst::JUMP: inst::jump(core); break;
				case Inst::CALL: inst::call(core); break;
				case Inst::RETURN: inst::reTurn(core); break;
				case Inst::IF: inst::iF(core); break;
				case Inst::INVOKE: inst::invoke(core); break;
				case Inst::EXTERNAL: inst::external(core); break;
				case Inst::CAPTURE: inst::capture(core); break;
				case Inst::PARAMETERS: inst::parameters(core); break;
					
				case Inst::NEWARR: inst::newarr(core); break;
				case Inst::NEWSTR: inst::newstr(core); break;
				case Inst::NEWOUT: inst::newout(core); break;
				case Inst::NEWIN: inst::newin(core); break;
				case Inst::NEWFX: inst::newfx(core); break;
				case Inst::NEWCLOCK: inst::newclock(core); break;
				case Inst::NEWSTRUCT: inst::newstruct(core); break;
				case Inst::NEWRANGE: inst::newrange(core); break;
				case Inst::NEWSTACK: inst::newstack(core); break;
				case Inst::NEWQUEUE: inst::newqueue(core); break;
				case Inst::NEWMAP: inst::newmap(core); break;
				case Inst::NEWRNG: inst::newrng(core); break;
				
				case Inst::READ: inst::read(core); break;
				case Inst::WRITE: inst::write(core); break;
				case Inst::SCRAP: inst::scrap(core); break;
				case Inst::DUPLICATE: inst::duplicate(core); break;
				case Inst::MAKEVAR: inst::makevar(core); break;
				case Inst::READ_X: inst::read_x(core); break;
				case Inst::WRITE_X: inst::write_x(core); break;
				case Inst::SWAP: inst::swap(core); break;

				case Inst::READ_0: inst::read_0(core); break;
				case Inst::READ_1: inst::read_1(core); break;
				case Inst::READ_2: inst::read_2(core); break;
				case Inst::READ_3: inst::read_3(core); break;
				case Inst::WRITE_0: inst::write_0(core); break;
				case Inst::WRITE_1: inst::write_1(core); break;
				case Inst::WRITE_2: inst::write_2(core); break;
				case Inst::WRITE_3: inst::write_3(core); break;

				case Inst::OUT: inst::out(core); break;
				case Inst::STYLIZE: inst::stylize(core); break;
				case Inst::CLOSE_STREAM: inst::close_stream(core); break;
				case Inst::IN_STR: inst::in_str(core); break;
				case Inst::IN_LINE: inst::in_line(core); break;
				case Inst::IN_BOOL: inst::in_bool(core); break;
				case Inst::IN_CHAR: inst::in_char(core); break;
				case Inst::IN_INT: inst::in_int(core); break;
				case Inst::IN_FLOAT: inst::in_float(core); break;
				case Inst::IN_ALL: inst::in_all(core); break;
				case Inst::IS_EOF: inst::is_eof(core); break;
				case Inst::IS_GOOD: inst::is_good(core); break;

				case Inst::MIN: inst::min(core); break;
				case Inst::MAX: inst::max(core); break;
				case Inst::ROUND: inst::round(core); break;
				case Inst::FLOOR: inst::floor(core); break;
				case Inst::CEIL: inst::ceil(core); break;
				case Inst::ABS: inst::abs(core); break;
				case Inst::HYPOT: inst::hypot(core); break;
				case Inst::SQRT: inst::sqrt(core); break;
				case Inst::LOG: inst::log(core); break;
				case Inst::LN: inst::ln(core); break;
				case Inst::POW: inst::pow(core); break;
				
				case Inst::SIN: inst::sin(core); break;
				case Inst::COS: inst::cos(core); break;
				case Inst::TAN: inst::tan(core); break;

				case Inst::BITAND: inst::bit_and(core); break;
				case Inst::BITOR: inst::bit_or(core); break;
				case Inst::BITXOR: inst::bit_xor(core); break;
				case Inst::BITNOT: inst::bit_not(core); break;
				
				case Inst::SIZE: inst::size(core); break;
				case Inst::AT: inst::at(core); break;
				case Inst::AT_WRITE: inst::at_write(core); break;
				case Inst::FRONT: inst::front(core); break;
				case Inst::BACK: inst::back(core); break;
				case Inst::INSERT: inst::insert(core); break;
				case Inst::REMOVE: inst::remove(core); break;
				case Inst::BEGIN: inst::begin(core); break;
				case Inst::END: inst::end(core); break;
				case Inst::PUSH: inst::push(core); break;
				case Inst::POP: inst::pop(core); break;
				case Inst::PEEK: inst::peek(core); break;
				case Inst::CONTAINS: inst::contains(core); break;

				case Inst::CAST_BOOL: inst::cast_bool(core); break;
				case Inst::CAST_CHAR: inst::cast_char(core); break;
				case Inst::CAST_INT: inst::cast_int(core); break;
				case Inst::CAST_FLOAT: inst::cast_float(core); break;
				case Inst::CAST_STRING: inst::cast_string(core); break;
				case Inst::CAST_ARRAY: inst::cast_array(core); break;

				case Inst::TYPEID: inst::type_id(core); break;
				case Inst::CLONE: inst::clone(core); break;

				case Inst::MEMBER_READ: inst::member_read(core); break;
				case Inst::MEMBER_WRITE: inst::member_write(core); break;

				case Inst::ALGORITHM: inst::algorithm(core); break;
				case Inst::RANDOM: inst::random(core); break;
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
