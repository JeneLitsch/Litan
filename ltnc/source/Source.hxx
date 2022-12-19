#pragma once
#include <string>
#include <istream>
#include <fstream>
#include "stdxx/memory.hxx"

namespace ltn::c {
	class Source {
	public:
		virtual std::unique_ptr<std::istream> make_istream() const = 0;
		virtual std::string get_name() const = 0; 
		virtual std::string get_full_name() const = 0; 
	private:
	};
}