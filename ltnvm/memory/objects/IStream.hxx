#pragma once
#include <memory>
#include <istream>
#include <iostream>
#include <string_view>
namespace ltn::vm {
	class IStream {
	public:
		IStream(std::istream & in)
			: ptr(&in) {}

		IStream(std::unique_ptr<std::istream> in) 
			: storage(std::move(in)), ptr(in.get()) {}

		std::istream & get() {
			return *ptr;
		}

		constexpr static std::string_view typeName = "IStream";
	private:
		std::shared_ptr<std::istream> storage;
		std::istream * ptr;
	};
}