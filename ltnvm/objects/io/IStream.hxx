#pragma once
#include <memory>
#include <istream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string_view>
#include "ltnvm/objects/Object.hxx"

namespace ltn::vm {
	class IStream : public Object {
	public:
		constexpr static std::string_view typeName = "IStream";

		virtual void stringify(VMCore & core, std::ostream & oss, bool nested) override;

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
	};



	inline IStream clone(const IStream &) {
		throw std::runtime_error{"Cannot clone IStream."};
	}
}