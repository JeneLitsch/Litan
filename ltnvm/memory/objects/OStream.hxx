#pragma once
#include <memory>
#include <ostream>
#include <iostream>
#include <string_view>
namespace ltn::vm {
	class OStream {
	public:
		constexpr static std::string_view typeName = "OStream";

		OStream(std::ostream & in)
			: ptr(&in) {}

		OStream(std::unique_ptr<std::ostream> && out) 
			: storage(std::move(out)), ptr(storage.get()) {}

		auto & get() {
			return *ptr;
		}

		const auto & get() const {
			return *ptr;
		}

		OStream clone() const {
			throw std::runtime_error{"Cannot clone OStream."};
		}

	private:
		std::unique_ptr<std::ostream> storage;
		std::ostream * ptr;
	};
}