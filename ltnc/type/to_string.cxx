#include "to_string.hxx"
#include "ltnc/type/Type.hxx"
#include <sstream>

namespace ltn::c::type {
	namespace {
		template<typename T>
		std::string to_string(const T &) {
			return T::type_name;
		}

		std::string to_string(const Array & array) {
			std::ostringstream oss;
			if(array.contains) {
				oss << Array::type_name << "<" << to_string(**array.contains) << ">";
			}
			else {
				oss << Array::type_name << "<>";
			}
			return oss.str();
		}
	}
	
	std::string to_string(const Type & type) {
		return std::visit([] (const auto & t) { return to_string(t); }, *type);
	}
}