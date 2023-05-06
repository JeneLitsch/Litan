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
#include "ltnvm/stringify.hxx"

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
		table[OpCode::TRY] = inst::tRy;
		table[OpCode::THROW] = inst::thr0w;
		table[OpCode::BUILD_IN] = inst::build_in;
		
		table[OpCode::ADD] = inst::add;
		table[OpCode::SUB] = inst::sub;
		table[OpCode::MLT] = inst::mlt;
		table[OpCode::DIV] = inst::div;
		table[OpCode::MOD] = inst::mod;
		table[OpCode::POW] = inst::pow;

		table[OpCode::EQL] = inst::eql;
		table[OpCode::UEQL] = inst::ueql;
		table[OpCode::LT] = inst::lt;
		table[OpCode::GT] = inst::gt;
		table[OpCode::LTEQL] = inst::smleql;
		table[OpCode::GTEQL] = inst::bgreql;

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
		table[OpCode::INVOKE_VARIADIC] = inst::invoke_variadic;
		table[OpCode::CAPTURE] = inst::capture;
		table[OpCode::FOR_NEXT] = inst::for_next;

		table[OpCode::NEWARR] = inst::newarr;
		table[OpCode::NEWSTR] = inst::newstr;
		table[OpCode::NEWFX] = inst::newfx;
		table[OpCode::NEWCLOCK] = inst::newclock;
		table[OpCode::NEWSTRUCT] = inst::newstruct;
		table[OpCode::NEWSTACK] = inst::newstack;
		table[OpCode::NEWQUEUE] = inst::newqueue;
		table[OpCode::NEWMAP] = inst::newmap;
		table[OpCode::NEWTUPLE] = inst::newtuple;
		table[OpCode::NEWTYPE] = inst::newtype;

		table[OpCode::SCRAP] = inst::scrap;
		table[OpCode::DUPLICATE] = inst::duplicate;
		table[OpCode::MAKEVAR] = inst::makevar;
		table[OpCode::READ_X] = inst::read_x;
		table[OpCode::WRITE_X] = inst::write_x;
		table[OpCode::SWAP] = inst::swap;
		table[OpCode::UNPACK] = inst::unpack;
		table[OpCode::READ_0] = inst::read_0;
		table[OpCode::READ_1] = inst::read_1;
		table[OpCode::READ_2] = inst::read_2;
		table[OpCode::READ_3] = inst::read_3;
		table[OpCode::WRITE_0] = inst::write_0;
		table[OpCode::WRITE_1] = inst::write_1;
		table[OpCode::WRITE_2] = inst::write_2;
		table[OpCode::WRITE_3] = inst::write_3;

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
		table[OpCode::ITER] = inst::iter;

		table[OpCode::CAST] = inst::cast;
		table[OpCode::SAFE_CAST] = inst::safe_cast;
		table[OpCode::CAST_BOOL] = inst::cast_bool;
		table[OpCode::CAST_CHAR] = inst::cast_char;
		table[OpCode::CAST_INT] = inst::cast_int;
		table[OpCode::CAST_FLOAT] = inst::cast_float;
		table[OpCode::CAST_STRING] = inst::cast_string;
		table[OpCode::COPY] = inst::copy;
		table[OpCode::SAFE_COPY] = inst::safe_copy;
		table[OpCode::CONVERSION] = inst::conversion;

		table[OpCode::MEMBER_READ] = inst::member_read;
		table[OpCode::MEMBER_WRITE] = inst::member_write;

		table[OpCode::GLOBAL_READ] = inst::static_read;
		table[OpCode::GLOBAL_WRITE] = inst::static_write;

		return table.array;
	});



	namespace {
		void error(VmCore & core, std::string msg) {
			const auto ref = core.heap.alloc<String>(std::move(msg));
			core.stack.push(value::string(ref));
			inst::thr0w(core);
		}



		void load_main_args(VmCore & core, const std::vector<String> & args) {
			const auto ref = core.heap.alloc<Array>({});
			core.stack.push(value::array(ref));
			for(const auto & arg : args) {
				const auto str = core.heap.alloc<String>(std::string(arg));
				auto & arr = core.heap.read<Array>(ref);
				arr.push_back(value::string(str));
			}
		}



		void load_variant_args(VmCore & core, const std::vector<Variant> & args) {
			for(const auto & arg : args) {
				core.stack.push(to_value(arg, core.heap));
			};
		}



		void jump_to_init(VmCore & core, const std::string & main, std::uint64_t arguments_count) {
			const auto main_fx = [&] () -> std::string {
				if(!main.empty()) return main;
				return core.function_table.contains("main(1)") ? "main(1)" : "main(0)";
			} ();
			if(!core.function_table.contains(main_fx)) throw std::runtime_error {
				"Program does not contain function " + main_fx
			};
			core.pc = core.code_begin + core.function_table.at(main_fx);
			core.stack.push_frame(core.code_end - 1, arguments_count);
		}
	}



	Value run_core(VmCore & core) {
		RESUME:
		try {
			while(true) {
				const std::uint8_t op_code = core.fetch_byte();
				instructions_table[op_code](core);
			}
		}

		catch(const Exception & err) {
			error(core, err.msg);
			goto RESUME;
		}

		catch(const Value & value) {
			return value;
		}
	}



	Value main_loop(VmCore & core) {
		RESUME:
		try {
			while(true) {
				const std::uint8_t op_code = core.fetch_byte();
				instructions_table[op_code](core);
			}
		}
		catch(const Exception & err) {
			error(core, err.msg);
			goto RESUME;
		}

		catch(const Value & value) {
			return value;
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

		this->byte_code = { it, std::end(code) };
		this->core.code_begin = std::data(this->byte_code);
		this->core.code_end = this->core.code_begin + std::size(this->byte_code);
		this->core.pc = this->core.code_begin;
		this->core.stack.reset();
		this->core.stack.reset();
		this->core.heap.reset();

		// init static variables 
		main_loop(core);
	}



	Variant LtnVM::run(const std::vector<String> & args, const std::string & main) {
		load_main_args(core, args);
		jump_to_init(core, main, 1);
		try {
			return to_variant(main_loop(this->core), core.heap);
		}
		catch(const Unhandled & err) {
			throw std::runtime_error { 
				"Unhandled exception: " + err.exception.msg
			};
		}
	}



	Variant LtnVM::run(
		const std::string & function_label,
		const std::vector<Variant> & args) {

		load_variant_args(core, args);
		jump_to_init(core, function_label, std::size(args));
		try {
			return to_variant(main_loop(this->core), core.heap);
		}
		catch(const Unhandled & err) {
			throw std::runtime_error { 
				"Unhandled exception: " + err.exception.msg
			};
		}
	}



	void LtnVM::set_global(
		const std::string & name,
		Variant variant) {

		if(!core.static_table.contains(name)) throw std::runtime_error {
			"Program does not contain global variable " + name
		};

		const auto address = core.static_table[name];
		this->core.static_variables[address] = to_value(variant, core.heap);
	}
}
