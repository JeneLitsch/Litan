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

		OStream(std::unique_ptr<std::ostream> && out) {
			this->ptr = out.get();
			this->storage = std::move(out);
		}

		OStream(std::unique_ptr<std::ostringstream> && out) {
			this->ptr = out.get();
			this->oss = out.get();
			this->storage = std::move(out);
		}

		auto & get() {
			return *ptr;
		}

		const auto & get() const {
			return *ptr;
		}

		OStream clone() const {
			throw std::runtime_error{"Cannot clone OStream."};
		}

		std::unique_ptr<std::ostream> storage;
		std::ostream * ptr = nullptr;
		std::ostringstream * oss = nullptr;
	};
}