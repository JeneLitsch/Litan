#include "convert.hxx"
#include "type_check.hxx"
#include "ltnvm/Exception.hxx"
#include "special_member.hxx"

namespace ltn::vm::convert {


	bool to_bool(const Value value, VMCore & core) {
		if(is_null(value))  return false;
		if(is_bool(value))  return value.b;
		if(is_char(value))  return value.c != '\0';
		if(is_int(value))   return value.i != 0;
		if(is_float(value)) return value.f != 0.0;

		if(is_struct(value)) {
			auto & strukt = *value::as<Struct>(value);
			if(auto fx = find_special_member<MemberCode::OPERATOR_BOOL>(strukt)) {
				auto result = run_special_member(core, *fx, value);
				if(is_bool(result)) {
					return result.b;
				} 
				throw except::invalid_argument("Special member {bool} must return bool");
			}
		}

		return true;
	}


	std::int64_t to_int(const Value value) {
		if(is_bool(value)) {
			return value.b;
		}	

		if(is_char(value)) {
			return value.c;
		}

		if(is_int(value)) {
			return value.i;
		}
		
		throw except::invalid_cast("Int");
	}


	stx::float64_t to_float(const Value value) {
		if(is_bool(value)) {
			return static_cast<stx::float64_t>(value.b);
		}

		if(is_char(value)) {
			return static_cast<stx::float64_t>(value.c);
		}

		if(is_int(value)) {
			return static_cast<stx::float64_t>(value.i);
		}

		if(is_float(value)) {
			return value.f;
		}
		throw except::invalid_cast("Float");
	}


	char to_char(const Value value) {
		if(is_bool(value)) {
			return value.c;
		}

		if(is_char(value)) {
			return value.c;
		}

		throw except::invalid_cast("Char");
	}


	std::string to_string(Value value) {
		if(is_string(value)) {
			return value::as<String>(value)->copy_to_std_string();
		}

		throw except::invalid_cast("String");
	}
}