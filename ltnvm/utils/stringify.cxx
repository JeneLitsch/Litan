#include "stringify.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/special_member.hxx"
#include "ltnvm/VM.hxx"

namespace ltn::vm {
	void print_element(const Value value, VMCore & core, std::ostream & oss) {
		stringify(value, core, oss, true);
	} 



	void print_element(const std::pair<Value, Value> pair, VMCore & core, std::ostream & oss) {
		const auto & [key, val] = pair;
		stringify(key, core, oss, true);
		oss << " : ";
		stringify(val, core, oss, true);
	}



	std::string stringify(const Value & value, VMCore & core) {
		std::ostringstream oss;
		stringify(value, core, oss, false);
		return oss.str();
	}



	void stringify_primitive(const Value & value, std::ostream & oss) {
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



	void stringify(const Value & value, VMCore & core, std::ostream & oss, bool nested) {
		if(is_object(value)) {
			value::as<Object>(value)->stringify(core, oss, nested);
			return;
		}

		if(is_type(value)) {
			oss << value::as_type_object(value)->name(core);
			return;
		}

		stringify_primitive(value, oss);
	}
}