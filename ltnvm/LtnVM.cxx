#include "LtnVM.hxx"
#include "ltn/opcodes.hxx"
#include <sstream>
#include "cast.hxx"
#include "inst/instructions.hxx"
#include "ltn/version.hxx"
#include "ltn/header.hxx"

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
		add_instruction(table, OpCode::EXIT, inst::exit);
		add_instruction(table, OpCode::ERROR, inst::error);
		add_instruction(table, OpCode::STATE, inst::state);
		add_instruction(table, OpCode::TRY, inst::tRy);
		add_instruction(table, OpCode::THROW, inst::thr0w);
		add_instruction(table, OpCode::BUILD_IN, inst::build_in);
		
		add_instruction(table, OpCode::ADD, inst::add);
		add_instruction(table, OpCode::SUB, inst::sub);
		add_instruction(table, OpCode::MLT, inst::mlt);
		add_instruction(table, OpCode::DIV, inst::div);
		add_instruction(table, OpCode::MOD, inst::mod);

		add_instruction(table, OpCode::EQL, inst::eql);
		add_instruction(table, OpCode::UEQL, inst::ueql);
		add_instruction(table, OpCode::SML, inst::sml);
		add_instruction(table, OpCode::BGR, inst::bgr);
		add_instruction(table, OpCode::SMLEQL, inst::smleql);
		add_instruction(table, OpCode::BGREQL, inst::bgreql);

		add_instruction(table, OpCode::SHIFT_L, inst::shift_l);
		add_instruction(table, OpCode::SHIFT_R, inst::shift_r);

		add_instruction(table, OpCode::NEG, inst::neg);
		add_instruction(table, OpCode::NOT, inst::n0t);
		add_instruction(table, OpCode::INC, inst::inc);
		add_instruction(table, OpCode::DEC, inst::dec);

		add_instruction(table, OpCode::COMP, inst::comp);
		add_instruction(table, OpCode::APPROX, inst::approx);
		add_instruction(table, OpCode::BETWEEN, inst::between);

		add_instruction(table, OpCode::NEWI, inst::newi);
		add_instruction(table, OpCode::NEWF, inst::newf);
		add_instruction(table, OpCode::NEWU, inst::newu);
		add_instruction(table, OpCode::NEWC, inst::newc);
		add_instruction(table, OpCode::TRUE, inst::truE);
		add_instruction(table, OpCode::FALSE, inst::falsE);
		add_instruction(table, OpCode::NVLL, inst::null);

		add_instruction(table, OpCode::JUMP, inst::jump);
		add_instruction(table, OpCode::CALL, inst::call);
		add_instruction(table, OpCode::RETURN, inst::reTurn);
		add_instruction(table, OpCode::IF, inst::iF);
		add_instruction(table, OpCode::INVOKE, inst::invoke);

		add_instruction(table, OpCode::EXTERNAL, inst::external);
		add_instruction(table, OpCode::CAPTURE, inst::capture);
		add_instruction(table, OpCode::PARAMETERS, inst::parameters);

		add_instruction(table, OpCode::NEWARR, inst::newarr);
		add_instruction(table, OpCode::NEWSTR, inst::newstr);
		add_instruction(table, OpCode::NEWOUT, inst::newout);
		add_instruction(table, OpCode::NEWIN, inst::newin);
		add_instruction(table, OpCode::NEWFX, inst::newfx);
		add_instruction(table, OpCode::NEWCLOCK, inst::newclock);
		add_instruction(table, OpCode::NEWSTRUCT, inst::newstruct);
		add_instruction(table, OpCode::NEWRANGE, inst::newrange);
		add_instruction(table, OpCode::NEWSTACK, inst::newstack);
		add_instruction(table, OpCode::NEWQUEUE, inst::newqueue);
		add_instruction(table, OpCode::NEWMAP, inst::newmap);
		add_instruction(table, OpCode::NEWRNG, inst::newrng);

		add_instruction(table, OpCode::READ, inst::read);
		add_instruction(table, OpCode::WRITE, inst::write);
		add_instruction(table, OpCode::SCRAP, inst::scrap);
		add_instruction(table, OpCode::DUPLICATE, inst::duplicate);
		add_instruction(table, OpCode::MAKEVAR, inst::makevar);
		add_instruction(table, OpCode::READ_X, inst::read_x);
		add_instruction(table, OpCode::WRITE_X, inst::write_x);
		add_instruction(table, OpCode::SWAP, inst::swap);
		add_instruction(table, OpCode::READ_0, inst::read_0);
		add_instruction(table, OpCode::READ_1, inst::read_1);
		add_instruction(table, OpCode::READ_2, inst::read_2);
		add_instruction(table, OpCode::READ_3, inst::read_3);
		add_instruction(table, OpCode::WRITE_0, inst::write_0);
		add_instruction(table, OpCode::WRITE_1, inst::write_1);
		add_instruction(table, OpCode::WRITE_2, inst::write_2);
		add_instruction(table, OpCode::WRITE_3, inst::write_3);

		add_instruction(table, OpCode::OUT, inst::out);
		add_instruction(table, OpCode::CLOSE_STREAM, inst::close_stream);
		add_instruction(table, OpCode::IN_STR, inst::in_str);
		add_instruction(table, OpCode::IN_LINE, inst::in_line);
		add_instruction(table, OpCode::IN_BOOL, inst::in_bool);
		add_instruction(table, OpCode::IN_CHAR, inst::in_char);
		add_instruction(table, OpCode::IN_INT, inst::in_int);
		add_instruction(table, OpCode::IN_FLOAT, inst::in_float);
		add_instruction(table, OpCode::IN_ALL, inst::in_all);
		add_instruction(table, OpCode::IS_EOF, inst::is_eof);
		add_instruction(table, OpCode::IS_GOOD, inst::is_good);

		add_instruction(table, OpCode::MIN, inst::min);
		add_instruction(table, OpCode::MAX, inst::max);
		add_instruction(table, OpCode::ROUND, inst::round);
		add_instruction(table, OpCode::FLOOR, inst::floor);
		add_instruction(table, OpCode::CEIL, inst::ceil);
		add_instruction(table, OpCode::ABS, inst::abs);
		add_instruction(table, OpCode::HYPOT, inst::hypot);
		add_instruction(table, OpCode::SQRT, inst::sqrt);
		add_instruction(table, OpCode::LOG, inst::log);
		add_instruction(table, OpCode::LN, inst::ln);
		add_instruction(table, OpCode::POW, inst::pow);
		add_instruction(table, OpCode::SIN, inst::sin);
		add_instruction(table, OpCode::COS, inst::cos);
		add_instruction(table, OpCode::TAN, inst::tan);

		add_instruction(table, OpCode::BITAND, inst::bit_and);
		add_instruction(table, OpCode::BITOR, inst::bit_or);
		add_instruction(table, OpCode::BITXOR, inst::bit_xor);
		add_instruction(table, OpCode::BITNOT, inst::bit_not);
		
		add_instruction(table, OpCode::SIZE, inst::size);
		add_instruction(table, OpCode::AT, inst::at);
		add_instruction(table, OpCode::AT_WRITE, inst::at_write);
		add_instruction(table, OpCode::FRONT, inst::front);
		add_instruction(table, OpCode::BACK, inst::back);
		add_instruction(table, OpCode::INSERT, inst::insert);
		add_instruction(table, OpCode::REMOVE, inst::remove);
		add_instruction(table, OpCode::BEGIN, inst::begin);
		add_instruction(table, OpCode::END, inst::end);
		add_instruction(table, OpCode::PUSH, inst::push);
		add_instruction(table, OpCode::POP, inst::pop);
		add_instruction(table, OpCode::PEEK, inst::peek);
		add_instruction(table, OpCode::CONTAINS, inst::contains);
		add_instruction(table, OpCode::EMPTY, inst::empty);

		add_instruction(table, OpCode::CAST_BOOL, inst::cast_bool);
		add_instruction(table, OpCode::CAST_CHAR, inst::cast_char);
		add_instruction(table, OpCode::CAST_INT, inst::cast_int);
		add_instruction(table, OpCode::CAST_FLOAT, inst::cast_float);
		add_instruction(table, OpCode::CAST_STRING, inst::cast_string);
		add_instruction(table, OpCode::CAST_ARRAY, inst::cast_array);

		add_instruction(table, OpCode::TYPEID, inst::type_id);
		add_instruction(table, OpCode::CLONE, inst::clone);

		add_instruction(table, OpCode::MEMBER_READ, inst::member_read);
		add_instruction(table, OpCode::MEMBER_WRITE, inst::member_write);

		add_instruction(table, OpCode::GLOBAL_READ, inst::global_read);
		add_instruction(table, OpCode::GLOBAL_WRITE, inst::global_write);

		return table;
	}

	const auto instructions_table = make_instruction_table();

	void LtnVM::setup(std::vector<std::uint8_t> code) {
		static constexpr auto get_uint8 = [] (auto & it) {
			return *(it++);
		};



		if(code.size() < 2) {
			throw std::runtime_error{"Not an executable program"};
		}

		auto it = std::begin(code);
		const std::uint8_t version = ltn::read_version(it);
		if(!is_compatible(version)) {
			throw std::runtime_error{"Incompatible bytecode version"};
		}

		this->core.mains = read_fx_table(it);

		this->core.byte_code = std::vector<std::uint8_t>{ it, std::end(code) };
		this->core.pc = 0;
		this->core.reg.reset();
		this->core.stack.reset();
		this->core.heap.reset();
	}

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

	Value LtnVM::run(const std::vector<std::string> & args, const std::string & main) {

		
		// load args
		const auto ref = this->core.heap.alloc<Array>(Array{});
		this->core.reg.push(value::array(ref));
		for(const auto & arg : args) {
			const auto str = this->core.heap.alloc<String>(String{arg});
			auto & arr = this->core.heap.read<Array>(ref).get();
			arr.push_back(value::string(str));
		}

		const auto main_fx = [&] () -> std::string {
			if(!main.empty()) return main;
			return core.mains.contains("main(1)") ? "main(1)" : "main(0)";
		} ();
		if(!core.mains.contains(main_fx)) throw std::runtime_error {
			"Program does not contain function " + main_fx
		};
		core.pc = core.mains.at(main_fx);
		core.stack.push_frame(std::size(core.byte_code) - 1);

		RESUME:
		try {
			while(true) {
				const std::uint8_t inst = this->core.fetch_byte();
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
