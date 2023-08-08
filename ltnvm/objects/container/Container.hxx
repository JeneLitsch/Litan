#pragma once
#include <vector>
#include <string_view>
#include "ltnvm/Value.hxx"
#include "ltnvm/objects/Object.hxx"

namespace ltn::vm {

	template<typename T>
	struct Container : public Object {
		using std_container = T; 
		using iterator = typename std_container::iterator;
		using const_iterator = typename std_container::const_iterator;
	protected:
		Container(std_container data = {}) : data {data} {}

	public:
		friend auto operator<=>(const Container & l, const Container & r) {
			return l.data <=> r.data;
		}

		inline void push_back(const Value & value) {
			++this->version;
			data.push_back(value);
		}

		void pop_back() {
			++this->version;
			this->data.pop_back();
		}

		void erase(iterator iter) {
			++this->version;
			this->data.erase(iter);
		}

		void replace_underlying(std_container new_data) {
			++this->version;
			this->data = std::move(new_data);
		}



		inline auto & operator[](std::uint64_t i) const {
			return this->data[i];
		}

		inline auto & operator[](std::uint64_t i) {
			return this->data[i];
		}

		inline bool empty() const {
			return std::empty(this->data);
		}

		inline std::uint64_t size() const {
			return std::size(this->data);
		}

		inline auto & front() const {
			return this->data.front();
		}

		inline auto & back() const {
			return this->data.back();
		}

		inline auto begin() { return std::begin(this->data); }
		inline auto end() { return std::end(this->data); }

		inline auto begin() const { return std::begin(this->data); }
		inline auto end() const { return std::end(this->data); }

		inline auto cbegin() const { return std::cbegin(this->data); }
		inline auto cend() const { return std::cend(this->data); }

		inline const std_container & get_underlying() const {
			return this->data;
		}

		std::uint64_t get_version() const {
			return this->version;
		}
	 
	protected:
		std_container data;
		std::uint64_t version = 0;
	};
}