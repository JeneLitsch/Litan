#include "instructions.hxx"
#include "stdxx/string.hxx"
#include "stdxx/array.hxx"
#include <cmath>
#include "ltnvm/type_check.hxx"
#include <sstream>
#include "ltnvm/Operations.hxx"
#include "ltnvm/calcBinary.hxx"
#include "ltnvm/convert.hxx"
#include "ltnvm/cast.hxx"

#define FETCH\
	const auto r = core.stack.pop();\
	const auto l = core.stack.pop();

namespace ltn::vm::inst {
	namespace {
		template<typename T>
		std::uint64_t concat(const Value & l, const Value & r, Heap & heap) {
			const auto obj_l = heap.read<T>(l.u);
			const auto obj_r = heap.read<T>(r.u);
			return heap.alloc<T>({obj_l + obj_r});
		} 



		template<typename Container>
		std::uint64_t repeat(
			const Value & ref,
			const Value & repetitions,
			Heap & heap) {
			
			const auto & str = heap.read<Container>(ref.u);
			const auto & count = cast::to_int(repetitions);
			auto repeated = stx::repeat(str, count);
			const auto ptr = heap.alloc<Container>(std::move(repeated)); 
			return ptr;
		}


		template<OperatorCode OP>
		void call_op(
			VmCore & core,
			const Value & self,
			const auto & ...args) {
			auto & strukt = core.heap.read<Struct>(self);
			const auto arity = 1 + sizeof...(args);
			for(const auto & [op, ref] : strukt.operators) {
				if(op == OP) {
					auto & fx = core.heap.read<FxPointer>(ref);
					if(fx.params != arity) throw except::invalid_parameters(arity, fx.params);
					if(fx.is_variadic) throw except::invalid_member_access();
					core.stack.push(self);
					(core.stack.push(args),...);
					core.stack.push_frame(core.pc, arity);
					core.pc = fx.ptr;
					return;
				}
			}
			switch (OP) {
				case OperatorCode::ADD: throw except::missing_operator("_+_");
				case OperatorCode::SUB: throw except::missing_operator("_-_");
				case OperatorCode::MLT: throw except::missing_operator("_*_");
				case OperatorCode::DIV: throw except::missing_operator("_/_");
				case OperatorCode::MOD: throw except::missing_operator("_%_");
				case OperatorCode::POW: throw except::missing_operator("_**_");
			}
		}
	}



	void add(VmCore & core) {
		FETCH

		if(is_array(l) && is_array(r)) {
			return core.stack.push(value::array(concat<Array>(l,r,core.heap)));
		}

		if(is_tuple(l) && is_tuple(r)) {
			return core.stack.push(value::tuple(concat<Array>(l,r,core.heap)));
		}

		if(is_string(l) && is_string(r)) {
			return core.stack.push(value::string(concat<String>(l,r,core.heap)));
		}

		if(is_struct(l)) {
			return call_op<OperatorCode::ADD>(core, l, r);
		}

		core.stack.push(calc<Addition>(l, r));
	}



	void sub(VmCore & core) {
		FETCH

		if(is_struct(l)) {
			return call_op<OperatorCode::SUB>(core, l, r);
		}

		core.stack.push(calc<Subtraction>(l, r));
	}



	void mlt(VmCore & core) {
		FETCH

		if(is_string(l) && is_integral(r)) {
			return core.stack.push(value::string(repeat<String>(l, r, core.heap)));
		}

		if(is_integral(l) && is_string(r)) {
			return core.stack.push(value::string(repeat<String>(r, l, core.heap)));
		}

		if(is_array(l) && is_integral(r)) {
			return core.stack.push(value::array(repeat<Array>(l, r, core.heap)));
		}

		if(is_integral(l) && is_array(r)) {
			return core.stack.push(value::array(repeat<Array>(r, l, core.heap)));
		}

		if(is_struct(l)) {
			return call_op<OperatorCode::MLT>(core, l, r);
		}

		core.stack.push(calc<Multiplication>(l, r));
	}



	void div(VmCore & core) {
		FETCH

		if(is_struct(l)) {
			return call_op<OperatorCode::DIV>(core, l, r);
		}

		core.stack.push(calc<Division>(l, r));
	}



	void mod(VmCore & core) {
		FETCH

		if(is_struct(l)) {
			return call_op<OperatorCode::MOD>(core, l, r);
		}
		
		core.stack.push(calc<Modulo>(l, r));
	}



	void pow(VmCore & core) {
		FETCH

		if(is_struct(l)) {
			return call_op<OperatorCode::POW>(core, l, r);
		}

		core.stack.push(calc<Power>(l, r));
	}
}
#undef FETCH