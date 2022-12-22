#pragma once
#include <string>
#include <istream>
#include <memory>

namespace ltn::c {
	class StringSource {
	public:
		StringSource(const std::string & name, const std::string & code);
		std::unique_ptr<std::istream> make_istream() const;
		std::string get_name() const;
		std::string get_full_name() const;
	private:
		std::string code;
		std::string name;
	};
}