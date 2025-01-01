#include "VM.hxx"
#include "litan_core/opcodes.hxx"
#include <sstream>
#include "litan_vm/utils/cast.hxx"
#include "inst/instructions.hxx"
#include "litan_core/version.hxx"
#include "litan_core/header.hxx"
#include "stdxx/iife.hxx"
#include "stdxx/keeper.hxx"
#include "litan_vm/utils/to_any.hxx"
#include "litan_vm/utils/to_value.hxx"
#include "litan_vm/utils/stringify.hxx"
#include "litan_vm/utils/json.hxx"

namespace ltn::vm {
	constexpr void add_instruction(auto & table, auto op_code, auto fx) {
		table[static_cast<std::size_t>(op_code)] = fx;
	}



	void illegal_instruction(VMCore &) {
		std::stringstream ss;
		ss << "Illegal Instruction";
		throw std::runtime_error{ss.str()};
	}



	constexpr auto instructions_table = stx::iife([] () {
		
		struct InstTableWrapper{
			using InstFx = void(*)(VMCore&);
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
		
		table[OpCode::NEWI] = inst::newi;
		table[OpCode::NEWF] = inst::newf;
		table[OpCode::TRUE] = inst::truE;
		table[OpCode::FALSE] = inst::falsE;
		table[OpCode::NVLL] = inst::null;
		table[OpCode::NEWI_SMALL] = inst::newi_small;

		table[OpCode::JUMP] = inst::jump;
		table[OpCode::CALL] = inst::call;
		table[OpCode::RETURN] = inst::reTurn;
		table[OpCode::IF] = inst::iF;
		table[OpCode::INVOKE] = inst::invoke;
		table[OpCode::CAPTURE] = inst::capture;
		table[OpCode::FOR_NEXT] = inst::for_next;
		table[OpCode::YIELD] = inst::yield;
		table[OpCode::CO_RETURN] = inst::co_retvrn;
		table[OpCode::CO_DUMP] = inst::co_dump;
		table[OpCode::RETURN_NULL] = inst::return_null;
		table[OpCode::TAIL] = inst::tail;

		table[OpCode::NEWARR] = inst::newarr;
		table[OpCode::NEWSTR] = inst::newstr;
		table[OpCode::NEWFX] = inst::newfx;
		table[OpCode::NEWSTRUCT] = inst::newstruct;
		table[OpCode::NEWMAP] = inst::newmap;
		table[OpCode::NEWTUPLE] = inst::newtuple;
		table[OpCode::NEWTYPE] = inst::newtype;

		table[OpCode::SCRAP] = inst::scrap;
		table[OpCode::DUPLICATE] = inst::duplicate;
		table[OpCode::LOAD_X] = inst::load_x;
		table[OpCode::STORE_X] = inst::store_x;
		table[OpCode::SWAP] = inst::swap;
		table[OpCode::UNPACK] = inst::unpack;
		table[OpCode::LOAD_0] = inst::load_0;
		table[OpCode::LOAD_1] = inst::load_1;
		table[OpCode::LOAD_2] = inst::load_2;
		table[OpCode::LOAD_3] = inst::load_3;
		table[OpCode::STORE_0] = inst::store_0;
		table[OpCode::STORE_1] = inst::store_1;
		table[OpCode::STORE_2] = inst::store_2;
		table[OpCode::STORE_3] = inst::store_3;
		
		table[OpCode::NEWI_CONST_0] = inst::newi_const_0;
		table[OpCode::NEWI_CONST_1] = inst::newi_const_1;
		table[OpCode::NEWI_CONST_2] = inst::newi_const_2;

		table[OpCode::BITAND] = inst::bit_and;
		table[OpCode::BITOR] = inst::bit_or;
		table[OpCode::BITXOR] = inst::bit_xor;
		table[OpCode::BITNOT] = inst::bit_not;

		table[OpCode::AT] = inst::at;
		table[OpCode::AT_WRITE] = inst::at_write;
		table[OpCode::ITER] = inst::iter;

		table[OpCode::CAST_BOOL] = inst::cast_bool;

		table[OpCode::MEMBER_READ] = inst::member_read;
		table[OpCode::MEMBER_WRITE] = inst::member_write;

		table[OpCode::GLOBAL_READ] = inst::static_read;
		table[OpCode::GLOBAL_WRITE] = inst::static_write;

		return table.array;
	});



	namespace {
		void error(VMCore & core, std::string msg) {
			const auto ref = core.heap.alloc(String{std::move(msg)});
			core.stack.push(value::string(ref));
			inst::thr0w(core);
		}



		void load_variant_args(VMCore & core, std::size_t argc, const Any * argv) {
			Tuple * tuple = core.heap.make<Tuple>();
			for(std::size_t i = 0; i < argc; ++i) {
				tuple->push_back(to_value(argv[i], core.heap));
			}
			core.stack.push(value::tuple(tuple));
		}



		void jump_to_init(VMCore & core, const std::string & main, std::uint64_t arguments_count) {
			const auto main_name = [&] () -> std::string {
				if(!main.empty()) return main;
				return core.function_pool.contains("main(1)") ? "main(1)" : "main(0)";
			} ();
			auto * main_fx = core.function_pool.get_by_name(main_name);
			if(!main_fx) throw std::runtime_error {
				"Program does not contain function " + main_name
			};

			core.pc = core.code_begin + main_fx->address;
			core.stack.push_frame(core.code_end - 1, 1, main_fx);
		}
	}



	Value run_core(VMCore & core) {
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



	Value main_loop(VMCore & core) {
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



	void VM::setup(std::span<const std::uint8_t> code) {
		if(code.size() < 2) {
			throw std::runtime_error{"Not an executable program"};
		}

		auto it = std::begin(code);
		const std::uint8_t version = ltn::read_version(it);
		if(!is_compatible(version)) {
			throw std::runtime_error{"Incompatible bytecode version"};
		}

		core.function_pool.read(it);
		core.string_pool.read(it);
		this->core.member_name_table = read_name_table(it);

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


	Any VM::call(
		const std::string & function_label,
		const std::vector<Any> & args) {
		
		return this->call(function_label, args.size(), args.data());
	}

	Any VM::call(
		const std::string & function_label,
		std::size_t argc,
		const Any * argv) {

		stx::keeper pc_keeper = this->core.pc;

		load_variant_args(core, argc, argv);
		jump_to_init(core, function_label, argc);
		try {
			auto ret = to_any(main_loop(this->core), core.heap);
			return ret;
		}
		catch(const Unhandled & err) {
			throw std::runtime_error { 
				"Unhandled exception: " + err.exception.msg
			};
		}
	}
}
