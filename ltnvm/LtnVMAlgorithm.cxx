#include "LtnVM.hxx"
#include "compare.hxx"
#include <algorithm>
#include <numeric>

namespace ltn::vm {
	auto toCppRange(const Value ref, Heap & heap) {
		if(isArr(ref)) {
			auto & array = heap.read<Array>(ref.u);
			const auto begin = array.arr.begin();
			const auto end = array.arr.end();
			return std::make_pair(begin, end);
		}

		if(isRange(ref)) {
			auto & range = heap.read<Range>(ref.u);
			auto & array = heap.read<Array>(range.array);
			const auto begin = array.arr.begin() + range.begin;
			const auto end = array.arr.begin() + range.end;
			return std::make_pair(begin, end);
		}
		throw std::runtime_error{"Algorithm need range or array"};
	}

	auto smaller(Heap & heap) {
		return [&heap] (const Value l, const Value r) {
			return compare(l, r, heap) < 0;
		};
	}

	auto bigger(Heap & heap) {
		return [&heap] (const Value l, const Value r) {
			return compare(l, r, heap) > 0;
		};
	}

	auto predicate(Heap & heap, const Value key) {
		return [&heap, key] (const Value elem) {
			return compare(elem, key, heap) == 0;
		};
	}

	void LtnVM::algorithm() {
		const auto ref = this->reg.pop();
		const auto type = this->fetchByte();
		const auto [begin, end] = toCppRange(ref, this->heap);

		switch (type) {
		case 1: {
			const auto comp = smaller(this->heap);
			std::sort(begin, end, comp);
		} break;
		
		case 2: {
			const auto comp = bigger(this->heap);
			std::sort(begin, end, comp);
		} break;

		case 0x10: {
			const auto key = this->reg.pop();
			const auto pred = predicate(this->heap, key);
			const auto found = std::find_if(begin, end, pred);
			if(found == end) {
				this->reg.push(static_cast<std::int64_t>(-1));
			}
			else {
				const auto index = std::distance(begin, found);
				this->reg.push(index);
			}
		} break;
		
		default: {
			std::runtime_error{"Invalid algorithm type"};
		} break;
		}
	}
}