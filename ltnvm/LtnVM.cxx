#include "LtnVM.hxx"
#include "ltn/opcodes.hxx"
#include <sstream>
#include "cast.hxx"
#include "inst/instructions.hxx"
#include "ltn/version.hxx"
#include "ltn/header.hxx"
#include "stdxx/iife.hxx"
#include "ltnvm/to_variant.hxx"
#include "ltnvm/to_value.hxx"

namespace ltn::vm {
	constexpr void add_instruction(auto & table, auto op_code, auto fx) {
		table[static_cast<std::size_t>(op_code)] = fx;
	}



	void illegal_instruction(VmCore &) {
		std::stringstream ss;
		ss << "Illegal Instruction";
		throw std::runtime_error{ss.str()};
	}



	constexpr auto instructions_table = stx::iife([] () {
		
		struct InstTableWrapper{
			using InstFx = void(*)(VmCore&);
			constexpr InstTableWrapper() {
				std::fill(std::begin(array), std::end(array), illegal_instruction);
			}
			std::array<InstFx, 256> array;

			constexpr InstFx & operator[](OpCode op_code) {
				return array[static_cast<std::size_t>(op_code)];
			}
		} table;

		table[OpCode::EXIT] = inst::exit;
		table[OpCode::ERROR] = inst::error;
		table[OpCode::STATE] = inst::state;
		table[OpCode::TRY] = inst::tRy;
		table[OpCode::THROW] = inst::thr0w;
		table[OpCode::BUILD_IN] = inst::build_in;
		
		table[OpCode::ADD] = inst::add;
		table[OpCode::SUB] = inst::sub;
		table[OpCode::MLT] = inst::mlt;
		table[OpCode::DIV] = inst::div;
		table[OpCode::MOD] = inst::mod;

		table[OpCode::EQL] = inst::eql;
		table[OpCode::UEQL] = inst::ueql;
		table[OpCode::SML] = inst::sml;
		table[OpCode::BGR] = inst::bgr;
		table[OpCode::SMLEQL] = inst::smleql;
		table[OpCode::BGREQL] = inst::bgreql;

		table[OpCode::SHIFT_L] = inst::shift_l;
		table[OpCode::SHIFT_R] = inst::shift_r;
		table[OpCode::NEG] = inst::neg;
		table[OpCode::NOT] = inst::n0t;
		table[OpCode::INC] = inst::inc;
		table[OpCode::DEC] = inst::dec;
		table[OpCode::DEREF] = inst::deref;
		table[OpCode::COMP] = inst::comp;
		table[OpCode::BETWEEN] = inst::between;
		
		table[OpCode::NEWI] = inst::newi;
		table[OpCode::NEWF] = inst::newf;
		table[OpCode::NEWC] = inst::newc;
		table[OpCode::TRUE] = inst::truE;
		table[OpCode::FALSE] = inst::falsE;
		table[OpCode::NVLL] = inst::null;

		table[OpCode::JUMP] = inst::jump;
		table[OpCode::CALL] = inst::call;
		table[OpCode::RETURN] = inst::reTurn;
		table[OpCode::IF] = inst::iF;
		table[OpCode::INVOKE] = inst::invoke;
		table[OpCode::EXTERNAL] = inst::external;
		table[OpCode::CAPTURE] = inst::capture;
		table[OpCode::PARAMETERS] = inst::parameters;

		table[OpCode::NEWARR] = inst::newarr;
		table[OpCode::NEWSTR] = inst::newstr;
		table[OpCode::NEWOUT] = inst::newout;
		table[OpCode::NEWIN] = inst::newin;
		table[OpCode::NEWFX] = inst::newfx;
		table[OpCode::NEWCLOCK] = inst::newclock;
		table[OpCode::NEWSTRUCT] = inst::newstruct;
		table[OpCode::NEWSTACK] = inst::newstack;
		table[OpCode::NEWQUEUE] = inst::newqueue;
		table[OpCode::NEWMAP] = inst::newmap;
		table[OpCode::NEWRNG] = inst::newrng;

		table[OpCode::SCRAP] = inst::scrap;
		table[OpCode::DUPLICATE] = inst::duplicate;
		table[OpCode::MAKEVAR] = inst::makevar;
		table[OpCode::READ_X] = inst::read_x;
		table[OpCode::WRITE_X] = inst::write_x;
		table[OpCode::SWAP] = inst::swap;
		table[OpCode::READ_0] = inst::read_0;
		table[OpCode::READ_1] = inst::read_1;
		table[OpCode::READ_2] = inst::read_2;
		table[OpCode::READ_3] = inst::read_3;
		table[OpCode::WRITE_0] = inst::write_0;
		table[OpCode::WRITE_1] = inst::write_1;
		table[OpCode::WRITE_2] = inst::write_2;
		table[OpCode::WRITE_3] = inst::write_3;

		table[OpCode::OUT] = inst::out;
		table[OpCode::CLOSE_STREAM] = inst::close_stream;
		table[OpCode::IN_STR] = inst::in_str;
		table[OpCode::IN_LINE] = inst::in_line;
		table[OpCode::IN_BOOL] = inst::in_bool;
		table[OpCode::IN_CHAR] = inst::in_char;
		table[OpCode::IN_INT] = inst::in_int;
		table[OpCode::IN_FLOAT] = inst::in_float;
		table[OpCode::IN_ALL] = inst::in_all;
		table[OpCode::IS_EOF] = inst::is_eof;
		table[OpCode::IS_GOOD] = inst::is_good;

		table[OpCode::MIN] = inst::min;
		table[OpCode::MAX] = inst::max;
		table[OpCode::ROUND] = inst::round;
		table[OpCode::FLOOR] = inst::floor;
		table[OpCode::CEIL] = inst::ceil;
		table[OpCode::ABS] = inst::abs;
		table[OpCode::HYPOT] = inst::hypot;
		table[OpCode::SQRT] = inst::sqrt;
		table[OpCode::LOG] = inst::log;
		table[OpCode::LN] = inst::ln;
		table[OpCode::POW] = inst::pow;
		table[OpCode::SIN] = inst::sin;
		table[OpCode::COS] = inst::cos;
		table[OpCode::TAN] = inst::tan;

		table[OpCode::BITAND] = inst::bit_and;
		table[OpCode::BITOR] = inst::bit_or;
		table[OpCode::BITXOR] = inst::bit_xor;
		table[OpCode::BITNOT] = inst::bit_not;

		table[OpCode::SIZE] = inst::size;
		table[OpCode::AT] = inst::at;
		table[OpCode::AT_WRITE] = inst::at_write;
		table[OpCode::FRONT] = inst::front;
		table[OpCode::BACK] = inst::back;
		table[OpCode::INSERT] = inst::insert;
		table[OpCode::REMOVE] = inst::remove;
		table[OpCode::PUSH] = inst::push;
		table[OpCode::POP] = inst::pop;
		table[OpCode::PEEK] = inst::peek;
		table[OpCode::CONTAINS] = inst::contains;
		table[OpCode::EMPTY] = inst::empty;

		table[OpCode::CAST] = inst::cast;
		table[OpCode::SAFE_CAST] = inst::safe_cast;
		table[OpCode::CAST_BOOL] = inst::cast_bool;
		table[OpCode::CAST_CHAR] = inst::cast_char;
		table[OpCode::CAST_INT] = inst::cast_int;
		table[OpCode::CAST_FLOAT] = inst::cast_float;
		table[OpCode::CAST_STRING] = inst::cast_string;
		table[OpCode::COPY] = inst::copy;
		table[OpCode::SAFE_COPY] = inst::safe_copy;

		table[OpCode::TYPEID] = inst::type_id;
		table[OpCode::CLONE] = inst::clone;

		table[OpCode::MEMBER_READ] = inst::member_read;
		table[OpCode::MEMBER_WRITE] = inst::member_write;

		table[OpCode::GLOBAL_READ] = inst::static_read;
		table[OpCode::GLOBAL_WRITE] = inst::static_write;

		return table.array;
	});



	void LtnVM::register_external(
		std::int64_t id,
		std::unique_ptr<ext::External> && ext) {
		this->core.externals.emplace(id, std::move(ext));
	}



	namespace {
		void error(VmCore & core, const std::string & msg) {
			const auto ref = core.heap.alloc<String>({msg});
			core.reg.push(value::string(ref));
			inst::thr0w(core);
		}



		Variant core_loop(VmCore & core) {
			RESUME:
			try {
				while(true) {
					const std::uint8_t inst = core.fetch_byte();
					instructions_table[inst](core);
				}
			}

			catch(const Exception & err) {
				error(core, err.msg);
				goto RESUME;
			}

			catch(const Value & value) {
				return to_variant(value, core.heap);
			}
		}



		void load_main_args(VmCore & core, const std::vector<std::string> & args) {
			const auto ref = core.heap.alloc<Array>(Array{});
			core.reg.push(value::array(ref));
			for(const auto & arg : args) {
				const auto str = core.heap.alloc<String>(String{arg});
				auto & arr = core.heap.read<Array>(ref).get();
				arr.push_back(value::string(str));
			}
		}



		void jump_to_init(VmCore & core, const std::string & main) {
			const auto main_fx = [&] () -> std::string {
				if(!main.empty()) return main;
				return core.function_table.contains("main(1)") ? "main(1)" : "main(0)";
			} ();
			if(!core.function_table.contains(main_fx)) throw std::runtime_error {
				"Program does not contain function " + main_fx
			};
			core.pc = core.function_table.at(main_fx);
			core.stack.push_frame(std::size(core.byte_code) - 1);
		}
	}



	void LtnVM::setup(std::span<const std::uint8_t> code) {
		if(code.size() < 2) {
			throw std::runtime_error{"Not an executable program"};
		}

		auto it = std::begin(code);
		const std::uint8_t version = ltn::read_version(it);
		if(!is_compatible(version)) {
			throw std::runtime_error{"Incompatible bytecode version"};
		}

		this->core.function_table = read_addr_table(it);
		this->core.static_table = read_addr_table(it);

		this->core.byte_code = { it, std::end(code) };
		this->core.pc = 0;
		this->core.reg.reset();
		this->core.stack.reset();
		this->core.heap.reset();

		// init static variables 
		core_loop(core);
	}



	Variant LtnVM::run(const std::vector<std::string> & args, const std::string & main) {
		load_main_args(core, args);
		jump_to_init(core, main);
		return core_loop(this->core);
	}



	void LtnVM::set_global(
		const std::string & name,
		Variant variant) {

		if(!core.static_table.contains(name)) throw std::runtime_error {
			"Program does not contain global variable " + name
		};

		const auto addr = core.static_table[name];
		this->core.static_variables[addr] = to_value(variant, core.heap);
	}
}
