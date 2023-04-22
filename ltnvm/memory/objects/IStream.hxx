#pragma once
#include <memory>
#include <istream>
#include <iostream>
#include <string_view>
namespace ltn::vm {
	class IStream {
	public:
		constexpr static std::string_view typeName = "IStream";

		IStream() : ptr(nullptr) {}

		IStream(std::istream & in)
			: ptr(&in) {}

		IStream(std::unique_ptr<std::istream> in) 
			: storage(std::move(in)), ptr(storage.get()) {}

		auto & get() {
			return *ptr;
		}

		const auto & get() const {
			return *ptr;
		}
		
		std::unique_ptr<std::istream> storage;
		std::istream * ptr;
		bool marked = false;
		bool in_use = false;
	};



	inline IStream clone(const IStream &) {
		throw std::runtime_error{"Cannot clone IStream."};
	}
}