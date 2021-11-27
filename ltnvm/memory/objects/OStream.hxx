#pragma once
#include <memory>
#include <ostream>
#include <iostream>
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

	private:
		std::shared_ptr<std::ostream> storage;
		std::ostream * ptr;
	};
}