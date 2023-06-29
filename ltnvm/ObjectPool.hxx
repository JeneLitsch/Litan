#pragma once
#include <vector>
#include <optional>
#include <cstdint>
#include <queue>
#include <stdexcept>

namespace ltn::vm {
	template<typename T>
	class ObjectPool {
		struct Bundle {
			T obj;
			bool in_use = false;
		};
	public:

		T & get(std::uint64_t id) {
			return objects[id].obj;
		}



		std::uint64_t alloc(T && obj) {
			if(reuse.empty()) {
				this->objects.push_back(Bundle {
					.obj = std::move(obj),
					.in_use = true,
				});
				return this->next_id++;
			}
			else {
				const auto id = this->reuse.front();
				this->reuse.pop();
				this->objects[id] = Bundle {
					.obj = std::move(obj),
					.in_use = true,
				};
				return id;
			}
		}



		void gc_mark(std::uint64_t id) {
			objects[id].obj.marked = true;
		}



		void gc_sweep() {
			for(std::uint64_t id = 0; id < std::size(this->objects); ++id){
				auto & [obj, in_use] = objects[id];
				if(!in_use) continue;
				if(!obj.marked) {
					in_use = false;
					reuse.push(id);
				}
				else {
					obj.marked = false;
				}
			}
		}



		void clear() {
			this->objects.clear();
			this->reuse = {};
			this->next_id = 0;
		}



		bool gc_is_marked(std::uint64_t id) const {
			return objects[id].obj.marked;
		}


		
		std::uint64_t capacity() const {
			return this->objects.size();
		}


		std::uint64_t utilized() const {
			return this->objects.size() - reuse.size();
		}
	private:

		std::vector<Bundle> objects;
		std::queue<std::uint64_t> reuse;
		std::uint64_t next_id = 0;
	};
}