#include "LtnVM.hxx"
#include "compare.hxx"
#include <algorithm>
#include <numeric>

namespace ltn::vm {
	namespace {
		auto to_cpp_range(const Value ref, Heap & heap) {
			if(is_array(ref)) {
				auto & array = heap.read<Array>(ref.u);
				const auto begin = array.arr.begin();
				const auto end = array.arr.end();
				return std::make_pair(begin, end);
			}

			if(is_range(ref)) {
				auto & range = heap.read<Range>(ref.u);
				auto & array = heap.read<Array>(range.array);
				const auto begin = array.arr.begin() + range.begin;
				const auto end = array.arr.begin() + range.end;
				return std::make_pair(begin, end);
			}
			throw except::invalid_argument();
		}


		std::uint64_t pop_array_ref(Register & reg) {
			const auto ref = reg.pop();
			if(!is_array(ref)) throw except::invalid_argument();
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
		void sort_desc(Register & reg, Heap & heap) {
			const auto ref = reg.pop();
			const auto [begin, end] = to_cpp_range(ref, heap);
			const auto comp = bigger(heap);
			std::sort(begin, end, comp);
		}


		void sort_ascn(Register & reg, Heap & heap) {
			const auto ref = reg.pop();
			const auto [begin, end] = to_cpp_range(ref, heap);
			const auto comp = smaller(heap);
			std::sort(begin, end, comp);
		}


		inline void is_sorted_ascn(Register & reg, Heap & heap) {
			const auto ref = reg.pop();
			const auto [begin, end] = to_cpp_range(ref, heap);
			const auto comp = smaller(heap);
			const bool result = std::is_sorted(begin, end, comp);
			reg.push(result);
		}


		inline void is_sorted_desc(Register & reg, Heap & heap) {
			const auto ref = reg.pop();
			const auto [begin, end] = to_cpp_range(ref, heap);
			const auto comp = bigger(heap);
			const bool result = std::is_sorted(begin, end, comp);
			reg.push(result);

		}


		void find(Register & reg, Heap & heap) {
			const auto ref = reg.pop();
			const auto [begin, end] = to_cpp_range(ref, heap);
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


		void copy_front(Register & reg, Heap & heap) {
			const auto ref = reg.pop();
			const auto [begin, end] = to_cpp_range(ref, heap);
			const auto refArr = pop_array_ref(reg);
			auto & array = heap.read<Array>(refArr).get();
			auto beginArr = array.begin();
			auto inserter = std::insert_iterator(array, beginArr);
			std::copy(begin, end, inserter);
		}


		void copy_back(Register & reg, Heap & heap) {
			const auto ref = reg.pop();
			const auto [begin, end] = to_cpp_range(ref, heap);
			const auto refArr = pop_array_ref(reg);
			auto & array = heap.read<Array>(refArr).get();
			auto inserter = std::back_inserter(array);
			std::copy(begin, end, inserter);
		}

		
		inline void fill(Register & reg, Heap & heap) {
			const auto ref = reg.pop();
			const auto [begin, end] = to_cpp_range(ref, heap);
			const auto value = reg.pop();
			std::fill(begin, end, value);
		}

		inline void reverse(Register & reg, Heap & heap) {
			const auto ref = reg.pop();
			const auto [begin, end] = to_cpp_range(ref, heap);
			std::reverse(begin, end);
		}
	}

	void LtnVM::algorithm() {
		const auto type = this->fetch_byte();
		switch (type) {
		case 0x00: return sort_ascn(     this->reg, this->heap);
		case 0x01: return sort_desc(     this->reg, this->heap);
		case 0x02: return is_sorted_ascn(this->reg, this->heap);
		case 0x03: return is_sorted_desc(this->reg, this->heap);
		case 0x10: return find(          this->reg, this->heap);
		case 0x20: return copy_front(    this->reg, this->heap);
		case 0x22: return copy_back(     this->reg, this->heap);
		case 0x30: return fill(          this->reg, this->heap);
		case 0x40: return reverse(       this->reg, this->heap);
		
		default: {
			throw std::runtime_error{"Invalid algorithm type"};
		} break;
		}
	}
}