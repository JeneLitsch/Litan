#pragma once
#include <vector>
#include <optional>
#include <cstdint>
#include <queue>
#include <stdexcept>

namespace ltn::vm {
	template<typename T>
	class ObjectPool {
		static constexpr std::size_t PAGE_SIZE = 512;
		using Page = std::array<T, PAGE_SIZE>;
	public:

		T * get(void * ptr) {
			return reinterpret_cast<T*>(ptr);
		}


		T * alloc(T && t) {
			if(reuse.empty()) {
				if(this->next_id >= std::size(this->pages) * PAGE_SIZE) {
					this->pages.push_back(std::make_unique<Page>());
				}
				auto & obj = this->get_slot(this->next_id) = std::move(t);
				obj.in_use = true;
				++this->next_id;
				return &obj;
			}
			else {
				const auto id = this->reuse.front();
				this->reuse.pop();
				auto & obj = this->get_slot(id) = std::move(t);
				obj.in_use = true;
				return &obj;
			}
		}



		inline void gc_mark(void * ptr) const {
			reinterpret_cast<T*>(ptr)->marked = true;
		}



		void gc_sweep() {
			for(std::uint64_t i = 0; i < this->next_id; ++i){
				auto & obj = (*pages[i/PAGE_SIZE])[i%PAGE_SIZE];
				if(!obj.marked && obj.in_use) {
					reuse.push(i);
					obj.in_use = false;
				}
				else {
					obj.marked = false;
				}
			}
		}



		void clear() {
			this->pages.clear();
			this->reuse = {};
			this->next_id = 0;
		}



		bool gc_is_marked(void * ptr) const {
			return reinterpret_cast<T*>(ptr)->marked;
		}


		
		std::uint64_t capacity() const {
			return this->pages.size() * PAGE_SIZE;
		}


		std::uint64_t utilized() const {
			return this->next_id - reuse.size();
		}
	private:

		T & get_slot(std::uint64_t id) {
			// std::cout << "PAGE: " << (id/PAGE_SIZE) << "\n"; 
			// std::cout << "SLOT: " << (id%PAGE_SIZE) << "\n"; 
			return (*pages[id/PAGE_SIZE])[id%PAGE_SIZE];
		}

		std::vector<std::unique_ptr<Page>> pages;
		std::queue<std::uint64_t> reuse;
		std::uint64_t next_id = 0;
	};
}