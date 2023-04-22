#pragma once
#include <vector>
#include <optional>
#include <cstdint>
#include <queue>
#include <stdexcept>

namespace ltn::vm {
	template<typename T>
	class ObjectPool {
		static constexpr auto PAGE_SIZE = 256;
		struct Bundle {
			T obj;
			bool in_use = false;
			bool marked = false;
		};
		using Page = std::array<Bundle, PAGE_SIZE>;
	public:

		T & get(std::uint64_t id) {
			return this->get_slot(id).obj;
		}


		std::uint64_t alloc(T && obj) {
			if(reuse.empty()) {
				if(this->next_id >= std::size(this->pages) * PAGE_SIZE) {
					this->pages.push_back(std::make_unique<Page>());
				}
				this->get_slot(this->next_id) = Bundle {
					.obj = std::move(obj),
					.in_use = true,
					.marked = false
				};
				return this->next_id++;
			}
			else {
				const auto id = this->reuse.front();
				this->reuse.pop();
				this->get_slot(id) = Bundle {
					.obj = std::move(obj),
					.in_use = true,
					.marked = false
				};
				return id;
			}
		}



		void gc_mark(std::uint64_t id) {
			this->get_slot(id).marked = true;
		}



		void gc_sweep() {
			for(std::uint64_t i_page = 0; i_page < std::size(this->pages); ++i_page){
				auto & page = this->pages[i_page];
				for(std::uint64_t i_slot = 0; i_slot < PAGE_SIZE; ++i_slot){
					auto & [obj, in_use, marked] = (*page)[i_slot];
					if(!in_use) continue;
					if(!marked) {
						in_use = false;
						reuse.push(i_page * PAGE_SIZE + i_slot);
					}
					else {
						marked = false;
					}
				}
			}
		}



		void clear() {
			this->pages.clear();
			this->reuse = {};
			this->next_id = 0;
		}



		bool gc_is_marked(std::uint64_t id) const {
			return this->get_slot(id).marked;
		}


		
		std::uint64_t capacity() const {
			return this->pages.size() * PAGE_SIZE;
		}


		std::uint64_t utilized() const {
			return this->next_id - reuse.size();
		}
	private:

		Bundle & get_slot(std::uint64_t id) {
			return (*pages[id/PAGE_SIZE])[id%PAGE_SIZE];
		}

		const Bundle & get_slot(std::uint64_t id) const {
			return (*pages[id/PAGE_SIZE])[id%PAGE_SIZE];
		}

		std::vector<std::unique_ptr<Page>> pages;
		std::queue<std::uint64_t> reuse;
		std::uint64_t next_id = 0;
	};
}