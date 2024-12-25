#include "CoroutineIterator.hxx"
#include "litan_vm/VMCore.hxx"
#include "litan_vm/utils/type_check.hxx"
#include "litan_vm/Exception.hxx"
#include "litan_vm/objects/Coroutine.hxx"
#include "litan_core/reserved_members.hxx"
#include "litan_vm/VMCore.hxx"
#include "litan_vm/Exception.hxx"
#include "litan_vm/objects/Coroutine.hxx"

namespace ltn::vm {
	Value run_core(VMCore & core);

	namespace {
		std::pair<Value, Value> run_coroutine(VMCore & core, const Coroutine * cor) {
			const auto prev = core.pc;
			core.pc = cor->resume_address;
			core.stack.push_frame(core.code_end - 1, 0, cor->context);
			for(const auto c : cor->local_variables) {
				core.stack.push(c);
			} 
			auto result = run_core(core);
			core.pc = prev;
			if(is_tuple(result)) {
				auto * tuple = value::as<Tuple>(result);
				if(tuple->size() == 2) {
					return { tuple->unsafe_at(0), tuple->unsafe_at(1) };
				}
			}
			throw std::runtime_error{"Cannot deconstruct coroutine return tuple"};
		}
		
		std::pair<Value, Value> run(VMCore & core, const Value & ref) {
			if(is_coroutine(ref)) return run_coroutine(core, value::as<Coroutine>(ref));
			throw std::runtime_error{"Not a coroutine!"};
		}
	}



	CoroutineIterator::CoroutineIterator(Coroutine * coroutine, VMCore * core) 
		: coroutine{value::coroutine(coroutine)}
		, core{core} {}



	CoroutineIterator::CoroutineIterator(std::nullptr_t, VMCore *) {}
	


	Value CoroutineIterator::next() {
		if(is_null(this->coroutine)) return value::iterator_stop;
		auto [cor, val] = run(*core, this->coroutine);
		this->coroutine = cor;
		return val;
	}



	Value CoroutineIterator::get() {
		if(is_null(this->coroutine)) return value::iterator_stop;
		auto [cor, val] = run(*core, this->coroutine);
		return val;
	}



	void CoroutineIterator::mark() {
		gc::mark(this->coroutine);
	}



	void CoroutineIterator::move(std::int64_t amount) {
		while(amount > 0) {
			auto [cor, val] = run(*core, this->coroutine);
			this->coroutine = cor;
			--amount;
		}
	}



	std::uint64_t CoroutineIterator::size() const {
		return 0;
	}



	std::unique_ptr<Iterator> CoroutineIterator::clone() const {
		return std::make_unique<CoroutineIterator>(*this);
	}
}