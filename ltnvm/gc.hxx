#pragma once
#include <vector>
#include <deque>
#include "Value.hxx"
#include "objects/objects.hxx"

namespace ltn::vm::gc {
	void mark(const Value & value);
	void mark(const std::vector<Value> & values);
	void mark(const std::deque<Value> & values);

	void mark_obj(Contiguous * obj);
	void mark_obj(String * obj);
	void mark_obj(IStream * obj);
	void mark_obj(Iterator * obj);
	void mark_obj(OStream * obj);
	void mark_obj(FxPointer * obj);
	void mark_obj(Struct * obj);
	void mark_obj(Segmented * obj);
	void mark_obj(Map * obj);
	void mark_obj(Clock * obj);
	void mark_obj(RandomEngine * obj);
	void mark_obj(CoRoutine * obj);

	std::uint64_t sweep(std::unique_ptr<Object> & start);
}