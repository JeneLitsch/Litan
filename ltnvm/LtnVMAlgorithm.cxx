#include "LtnVM.hxx"
#include "compare.hxx"
#include <algorithm>
#include <numeric>

namespace ltn::vm {
	namespace {
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
			throw except::invalidArgument();
		}


		std::uint64_t popArrayRef(Register & reg) {
			const auto ref = reg.pop();
			if(!isArr(ref)) throw except::invalidArgument();
			return ref.u;
		}


		// Functions to pass to alogrithm
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




		// Algorithms
		void sort_desc(auto begin, auto end, Heap & heap) {
			const auto comp = bigger(heap);
			std::sort(begin, end, comp);
		}


		void sort_ascn(auto begin, auto end, Heap & heap) {
			const auto comp = smaller(heap);
			std::sort(begin, end, comp);
		}


		inline void is_sorted_ascn(auto begin, auto end, Register & reg, Heap & heap) {
			const auto comp = smaller(heap);
			const bool result = std::is_sorted(begin, end, comp);
			reg.push(result);
		}


		inline void is_sorted_desc(auto begin, auto end, Register & reg, Heap & heap) {
			const auto comp = bigger(heap);
			const bool result = std::is_sorted(begin, end, comp);
			reg.push(result);

		}


		void find(auto begin, auto end, Register & reg, Heap & heap) {
			const auto key = reg.pop();
			const auto pred = predicate(heap, key);
			const auto found = std::find_if(begin, end, pred);
			if(found == end) {
				reg.push(value::integer(-1));
			}
			else {
				const auto dist = std::distance(begin, found); 
				reg.push(value::integer(dist));
			}
		}


		void copy_front(auto begin, auto end, Register & reg, Heap & heap) {
			const auto refArr = popArrayRef(reg);
			auto & array = heap.read<Array>(refArr).get();
			auto beginArr = array.begin();
			auto inserter = std::insert_iterator(array, beginArr);
			std::copy(begin, end, inserter);
		}


		void copy_back(auto begin, auto end, Register & reg, Heap & heap) {
			const auto refArr = popArrayRef(reg);
			auto & array = heap.read<Array>(refArr).get();
			auto inserter = std::back_inserter(array);
			std::copy(begin, end, inserter);
		}

		
		inline void fill(auto begin, auto end, Register & reg) {
			const auto value = reg.pop();
			std::fill(begin, end, value);
		}
	}

	void LtnVM::algorithm() {
		const auto ref = this->reg.pop();
		const auto type = this->fetchByte();
		const auto [begin, end] = toCppRange(ref, this->heap);

		switch (type) {
		case 0x00: return sort_ascn(begin, end, this->heap);
		case 0x01: return sort_desc(begin, end, this->heap);
		case 0x02: return is_sorted_ascn(begin, end, this->reg, this->heap);
		case 0x03: return is_sorted_desc(begin, end, this->reg, this->heap);
		
		case 0x10: return find(begin, end, this->reg, this->heap);
		
		case 0x20: return copy_front(begin, end, this->reg, this->heap);
		case 0x22: return copy_back(begin, end, this->reg, this->heap);

		case 0x30: return fill(begin, end, this->reg);
		
		case 0x40: return std::reverse(begin, end);
		
		default: {
			throw std::runtime_error{"Invalid algorithm type"};
		} break;
		}
	}
}