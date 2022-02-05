#include "Map.hxx"
#include "ltnvm/memory/Heap.hxx"
namespace ltn::vm {
	bool Comparator::operator()(const Value l, const Value r) const {
		return compare(l, r, *heap) < 0;
	}
}