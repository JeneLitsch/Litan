#include "RangeCore.hxx"

namespace ltn::vm::iter {
	RangeCore::RangeCore(std::int64_t begin, std::int64_t end, std::int64_t step)
		: begin{begin}
		, end{end}
		, step{step}
		, current{begin} {}
	


	Value RangeCore::next(Heap &) {
		const bool backwards = this->begin <= this->end;
		const auto done = backwards
			? this->current >= this->begin && this->current < this->end
			: this->current <= this->begin && this->current > this->end;

		if(done) {
			auto prev = this->current;
			this->current += this->step;
			return value::integer(prev);
		}
		else {
			return value::iterator_stop;
		}
	}



	Value RangeCore::get(Heap &) {
		const bool backwards = this->begin <= this->end;
		const auto done = backwards
			? this->current >= this->begin && this->current < this->end
			: this->current <= this->begin && this->current > this->end;

		if(done) {
			return value::integer(this->current);
		}
		else {
			return value::iterator_stop;
		}
	}


	
	void RangeCore::move(Heap &, std::uint64_t amount) {
		this->current += amount * this->step;
	}
}