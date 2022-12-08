#include "to_string.hxx"
#include "ltnc/type/Type.hxx"
#include <sstream>

namespace ltn::c::type {
	namespace {
		template<typename T>
		std::string to_string(const T &) {
			return T::type_name;
		}


		std::string to_string(const Other & other) {
			return other.type_name;
		}


		std::string to_string(const Optional & optional) {
			std::ostringstream oss;
			oss << Optional::type_name << "<" << to_string(*optional.contains) << ">";
			return oss.str();
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


		std::string to_string(const Queue & queue) {
			std::ostringstream oss;
			oss << Queue::type_name << "<" << to_string(*queue.contains) << ">";
			return oss.str();
		}


		std::string to_string(const Stack & stack) {
			std::ostringstream oss;
			oss << Stack::type_name << "<" << to_string(*stack.contains) << ">";
			return oss.str();
		}

		
		std::string to_string(const Map & map) {
			std::ostringstream oss;
			if(map.val && map.key) {
				oss << Map::type_name << "<" << to_string(**map.key) << ", " << to_string(**map.val) << ">";
			}
			else {
				oss << Map::type_name << "<>";
			}
			return oss.str();
		}



		std::string to_string(const FxPtr & fx_ptr) {
			std::ostringstream oss;
			oss << FxPtr::type_name << "<";
			if(fx_ptr.return_type) oss << to_string(**fx_ptr.return_type);
			oss << "(";
			for(std::size_t i = 0; i < fx_ptr.parameter_types.size(); ++i) {
				if(i != 0) oss << ", ";
				oss << to_string(fx_ptr.parameter_types[i]);
			}
			oss << ")";
			oss << ">";
			return oss.str();
		}
	}
	
	std::string to_string(const Type & type) {
		return std::visit([] (const auto & t) { return to_string(t); }, *type);
	}
}