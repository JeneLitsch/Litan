#include "LtnVM.hxx"
#include "ltn/InstructionSet.hxx"
#include <sstream>
#include "cast.hxx"
#include "inst/instructions.hxx"

namespace ltn::vm {
	using InstFx = void(*)(VmCore&);

	constexpr void add_instruction(auto & table, auto op_code, auto fx) {
		table[static_cast<std::size_t>(op_code)] = fx;
	}

	void illegal_instruction(VmCore & core) {
		std::stringstream ss;
		ss << "Illegal Instruction";
		throw std::runtime_error{ss.str()};
	}



	constexpr auto make_instruction_table() {
		std::array<InstFx, 256> table;
		std::fill(std::begin(table), std::end(table), illegal_instruction);
		add_instruction(table, Inst::EXIT, inst::exit);
		add_instruction(table, Inst::ERROR, inst::error);
		add_instruction(table, Inst::STATE, inst::state);
		add_instruction(table, Inst::TRY, inst::tRy);
		add_instruction(table, Inst::THROW, inst::thr0w);
		add_instruction(table, Inst::ADD, inst::add);
		add_instruction(table, Inst::SUB, inst::sub);
		add_instruction(table, Inst::MLT, inst::mlt);
		add_instruction(table, Inst::DIV, inst::div);
		add_instruction(table, Inst::MOD, inst::mod);
		add_instruction(table, Inst::EQL, inst::eql);
		add_instruction(table, Inst::UEQL, inst::ueql);
		add_instruction(table, Inst::SML, inst::sml);
		add_instruction(table, Inst::BGR, inst::bgr);
		add_instruction(table, Inst::SMLEQL, inst::smleql);
		add_instruction(table, Inst::BGREQL, inst::bgreql);
		add_instruction(table, Inst::SHIFT_L, inst::shift_l);
		add_instruction(table, Inst::SHIFT_R, inst::shift_r);
		add_instruction(table, Inst::NEG, inst::neg);
		add_instruction(table, Inst::NOT, inst::n0t);
		add_instruction(table, Inst::INC, inst::inc);
		add_instruction(table, Inst::DEC, inst::dec);
		add_instruction(table, Inst::COMP, inst::comp);
		add_instruction(table, Inst::APPROX, inst::approx);
		add_instruction(table, Inst::BETWEEN, inst::between);
		add_instruction(table, Inst::NEWI, inst::newi);
		add_instruction(table, Inst::NEWF, inst::newf);
		add_instruction(table, Inst::NEWU, inst::newu);
		add_instruction(table, Inst::NEWC, inst::newc);
		add_instruction(table, Inst::TRUE, inst::truE);
		add_instruction(table, Inst::FALSE, inst::falsE);
		add_instruction(table, Inst::NVLL, inst::null);
		add_instruction(table, Inst::JUMP, inst::jump);
		add_instruction(table, Inst::CALL, inst::call);
		add_instruction(table, Inst::RETURN, inst::reTurn);
		add_instruction(table, Inst::IF, inst::iF);
		add_instruction(table, Inst::INVOKE, inst::invoke);
		add_instruction(table, Inst::EXTERNAL, inst::external);
		add_instruction(table, Inst::CAPTURE, inst::capture);
		add_instruction(table, Inst::PARAMETERS, inst::parameters);
		add_instruction(table, Inst::NEWARR, inst::newarr);
		add_instruction(table, Inst::NEWSTR, inst::newstr);
		add_instruction(table, Inst::NEWOUT, inst::newout);
		add_instruction(table, Inst::NEWIN, inst::newin);
		add_instruction(table, Inst::NEWFX, inst::newfx);
		add_instruction(table, Inst::NEWCLOCK, inst::newclock);
		add_instruction(table, Inst::NEWSTRUCT, inst::newstruct);
		add_instruction(table, Inst::NEWRANGE, inst::newrange);
		add_instruction(table, Inst::NEWSTACK, inst::newstack);
		add_instruction(table, Inst::NEWQUEUE, inst::newqueue);
		add_instruction(table, Inst::NEWMAP, inst::newmap);
		add_instruction(table, Inst::NEWRNG, inst::newrng);
		add_instruction(table, Inst::READ, inst::read);
		add_instruction(table, Inst::WRITE, inst::write);
		add_instruction(table, Inst::SCRAP, inst::scrap);
		add_instruction(table, Inst::DUPLICATE, inst::duplicate);
		add_instruction(table, Inst::MAKEVAR, inst::makevar);
		add_instruction(table, Inst::READ_X, inst::read_x);
		add_instruction(table, Inst::WRITE_X, inst::write_x);
		add_instruction(table, Inst::SWAP, inst::swap);
		add_instruction(table, Inst::READ_0, inst::read_0);
		add_instruction(table, Inst::READ_1, inst::read_1);
		add_instruction(table, Inst::READ_2, inst::read_2);
		add_instruction(table, Inst::READ_3, inst::read_3);
		add_instruction(table, Inst::WRITE_0, inst::write_0);
		add_instruction(table, Inst::WRITE_1, inst::write_1);
		add_instruction(table, Inst::WRITE_2, inst::write_2);
		add_instruction(table, Inst::WRITE_3, inst::write_3);
		add_instruction(table, Inst::OUT, inst::out);
		add_instruction(table, Inst::STYLIZE, inst::stylize);
		add_instruction(table, Inst::CLOSE_STREAM, inst::close_stream);
		add_instruction(table, Inst::IN_STR, inst::in_str);
		add_instruction(table, Inst::IN_LINE, inst::in_line);
		add_instruction(table, Inst::IN_BOOL, inst::in_bool);
		add_instruction(table, Inst::IN_CHAR, inst::in_char);
		add_instruction(table, Inst::IN_INT, inst::in_int);
		add_instruction(table, Inst::IN_FLOAT, inst::in_float);
		add_instruction(table, Inst::IN_ALL, inst::in_all);
		add_instruction(table, Inst::IS_EOF, inst::is_eof);
		add_instruction(table, Inst::IS_GOOD, inst::is_good);
		add_instruction(table, Inst::MIN, inst::min);
		add_instruction(table, Inst::MAX, inst::max);
		add_instruction(table, Inst::ROUND, inst::round);
		add_instruction(table, Inst::FLOOR, inst::floor);
		add_instruction(table, Inst::CEIL, inst::ceil);
		add_instruction(table, Inst::ABS, inst::abs);
		add_instruction(table, Inst::HYPOT, inst::hypot);
		add_instruction(table, Inst::SQRT, inst::sqrt);
		add_instruction(table, Inst::LOG, inst::log);
		add_instruction(table, Inst::LN, inst::ln);
		add_instruction(table, Inst::POW, inst::pow);
		add_instruction(table, Inst::SIN, inst::sin);
		add_instruction(table, Inst::COS, inst::cos);
		add_instruction(table, Inst::TAN, inst::tan);
		add_instruction(table, Inst::BITAND, inst::bit_and);
		add_instruction(table, Inst::BITOR, inst::bit_or);
		add_instruction(table, Inst::BITXOR, inst::bit_xor);
		add_instruction(table, Inst::BITNOT, inst::bit_not);
		add_instruction(table, Inst::SIZE, inst::size);
		add_instruction(table, Inst::AT, inst::at);
		add_instruction(table, Inst::AT_WRITE, inst::at_write);
		add_instruction(table, Inst::FRONT, inst::front);
		add_instruction(table, Inst::BACK, inst::back);
		add_instruction(table, Inst::INSERT, inst::insert);
		add_instruction(table, Inst::REMOVE, inst::remove);
		add_instruction(table, Inst::BEGIN, inst::begin);
		add_instruction(table, Inst::END, inst::end);
		add_instruction(table, Inst::PUSH, inst::push);
		add_instruction(table, Inst::POP, inst::pop);
		add_instruction(table, Inst::PEEK, inst::peek);
		add_instruction(table, Inst::CONTAINS, inst::contains);
		add_instruction(table, Inst::CAST_BOOL, inst::cast_bool);
		add_instruction(table, Inst::CAST_CHAR, inst::cast_char);
		add_instruction(table, Inst::CAST_INT, inst::cast_int);
		add_instruction(table, Inst::CAST_FLOAT, inst::cast_float);
		add_instruction(table, Inst::CAST_STRING, inst::cast_string);
		add_instruction(table, Inst::CAST_ARRAY, inst::cast_array);
		add_instruction(table, Inst::TYPEID, inst::type_id);
		add_instruction(table, Inst::CLONE, inst::clone);
		add_instruction(table, Inst::MEMBER_READ, inst::member_read);
		add_instruction(table, Inst::MEMBER_WRITE, inst::member_write);
		add_instruction(table, Inst::ALGORITHM, inst::algorithm);
		add_instruction(table, Inst::RANDOM, inst::random);

		return table;
	}

	const auto instructions_table = make_instruction_table();
 
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
				instructions_table[inst](core);
			}

		}
		catch(const Exception & error) {
			this->error(error.msg);
			goto RESUME;
		}

		catch(const Value & value) {
			return value;
		}
	}
}
