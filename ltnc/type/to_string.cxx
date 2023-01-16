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
			oss << "optional" << "<" << to_string(optional.contains) << ">";
			return oss.str();
		}



		std::string to_string(const Array & array) {
			std::ostringstream oss;
			if(array.contains) {
				oss << "array" << "<" << to_string(*array.contains) << ">";
			}
			else {
				oss << "array" << "<>";
			}
			return oss.str();
		}



		std::string to_string(const Tuple & tuple) {
			std::ostringstream oss;
			if(tuple.contained.empty()) {
				oss << "tuple" << "<>";
			}
			else {
				oss << "tuple" << "<";
				for(std::size_t i = 0; i < tuple.contained.size(); ++i) {
					if(i != 0) oss << ", ";
					oss << to_string(tuple.contained[i]);
				}
				oss << ">";
			}
			return oss.str();
		}



		std::string to_string(const Queue & queue) {
			std::ostringstream oss;
			oss << "queue" << "<" << to_string(queue.contains) << ">";
			return oss.str();
		}



		std::string to_string(const Stack & stack) {
			std::ostringstream oss;
			oss << "stack" << "<" << to_string(stack.contains) << ">";
			return oss.str();
		}


		
		std::string to_string(const Map & map) {
			std::ostringstream oss;
			oss << "map" << "<" << to_string(map.key) << ", " << to_string(map.val) << ">";
			return oss.str();
		}



		std::string to_string(const FxPtr & fx_ptr) {
			std::ostringstream oss;
			oss << "(";
			for(std::size_t i = 0; i < fx_ptr.parameter_types.size(); ++i) {
				if(i != 0) oss << ", ";
				oss << to_string(fx_ptr.parameter_types[i]);
			}
			oss << ")";
			oss << "->";
			oss << to_string(fx_ptr.return_type);
			return oss.str();
		}
	}
	

	
	std::string to_string(const Type & type) {
		return visit(type, [] (const auto & t) { return to_string(t); });
	}
}