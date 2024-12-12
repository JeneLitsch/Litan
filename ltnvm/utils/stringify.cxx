#include "stringify.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/special_member.hxx"
#include "ltnvm/VM.hxx"

namespace ltn::vm {
	void print_element(const Value value, VMCore & core, std::ostream & oss) {
		stringify(value, core, oss);
	} 



	void print_element(const std::pair<Value, Value> pair, VMCore & core, std::ostream & oss) {
		const auto & [key, val] = pair;
		stringify(key, core, oss);
		oss << " : ";
		stringify(val, core, oss);
	}



	std::string stringify(const Value & value, VMCore & core) {
		std::ostringstream oss;
		stringify(value, core, oss);
		return oss.str();
	}



	void stringify_primitive(const Value & value, VMCore & core, std::ostream & oss) {
		if(is_null(value)) {
			oss << "null";
			return;
		}

		if(is_iterator_stop(value)) {
			oss << "<iterator_stop>";
			return;
		}

		if(is_bool(value)) {
			oss << std::boolalpha << value.b;
			return;
		}

		if(is_char(value)) {
			oss << std::string(1, value.c);
			return;
		}

		if(is_int(value)) {
			oss << value.i;
			return;
		}

		if(is_float(value)) {
			oss << value.f;
			return;
		}
	}



	void stringify(const Value & value, VMCore & core, std::ostream & oss) {
		if(is_object(value)) {
			value::as<Object>(value)->stringify(core, oss, false);
			return;
		}

		if(is_type(value)) {
			oss << value::as_type_object(value)->name(core);
			return;
		}

		stringify_primitive(value, core, oss);
	}
}