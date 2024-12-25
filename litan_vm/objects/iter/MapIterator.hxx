#pragma once
#include <cstdint>
#include "litan_vm/Value.hxx"
#include "Iterator.hxx"
#include "litan_vm/objects/container.hxx"

namespace ltn::vm {
	class MapIterator : public Iterator {
	public:
		MapIterator(Map * container, Heap * heap);

		virtual Value next() override;
		virtual Value get() override;
		virtual void move(std::int64_t amount) override;
		virtual void mark() override;
		virtual std::uint64_t size() const override;
		virtual std::unique_ptr<Iterator> clone() const override;

	private:
		Map * map;
		Map::iterator iterator;
		std::uint64_t version;
		Heap * heap;
		Value current_key;
	};
}