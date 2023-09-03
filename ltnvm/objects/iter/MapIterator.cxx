#include "MapIterator.hxx"
#include "ltnvm/VMCore.hxx"
#include "ltnvm/Exception.hxx"

namespace ltn::vm {
	MapIterator::MapIterator(Map * map, Heap * heap)
		: Iterator{}
		, map{map}
		, iterator{std::begin(*map)}
		, version{map->get_version()}
		, heap{heap} {}	
	
	
	Value MapIterator::next() {
		auto value = this->get();
		this->move(!is_iterator_stop(value));
		return value;
	}



	Value MapIterator::get() {
		if(this->version != this->map->get_version()) {
			throw except::out_of_range("Invalidated map iterator");
		}
		if(this->iterator == this->map->end()) {
			return value::iterator_stop;
		}
		Tuple * tuple = this->heap->make<Tuple>();
		tuple->push_back(this->iterator->first);
		tuple->push_back(this->iterator->second);
		return value::tuple(tuple);
	}



	void MapIterator::move(std::int64_t amount) {
		if(this->version != this->map->get_version()) {
			throw except::out_of_range("Invalidated map iterator");
		}
		std::advance(this->iterator, amount);
	}



	void MapIterator::mark() {
		gc::mark(value::map(this->map));
	}



	std::uint64_t MapIterator::size() const {
		return this->map->size();
	}



	std::unique_ptr<Iterator> MapIterator::clone() const {
		return std::make_unique<MapIterator>(*this);
	}
}