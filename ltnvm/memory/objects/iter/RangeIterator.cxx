#include "RangeIterator.hxx"
#include "ltnvm/type_check.hxx"

namespace ltn::vm {
	RangeIterator::RangeIterator(std::int64_t begin, std::int64_t end, std::int64_t step)
		: begin{begin}
		, end{end}
		, step{step}
		, current{begin} {}
	


	Value RangeIterator::next(Heap & heap) {
		const auto value = this->get(heap);
		this->current += this->step * !is_iterator_stop(value);
		return value;
	}



	Value RangeIterator::get(Heap &) {
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


	
	void RangeIterator::move(Heap &, std::int64_t amount) {
		this->current += amount * this->step;
	}
}