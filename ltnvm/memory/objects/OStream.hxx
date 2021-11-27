#pragma once
#include <memory>
#include <ostream>
#include <iostream>
#include <string_view>
namespace ltn::vm {
	class OStream {
	public:
		OStream(std::ostream & in)
			: ptr(&in) {}

		OStream(std::unique_ptr<std::ostream> in) 
			: storage(std::move(in)), ptr(storage.get()) {}

		std::ostream & get() {
			return *ptr;
		}

		constexpr static std::string_view typeName = "OStream";
	private:
		std::shared_ptr<std::ostream> storage;
		std::ostream * ptr;
	};
}