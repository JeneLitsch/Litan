#include "type_name.hxx"
#include "ltn/type_code.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/memory/Heap.hxx"
#include "ltnvm/objects/type/decode_type.hxx"

namespace ltn::vm {
	struct TypeName {
		static std::string for_any(const std::uint8_t *)  {
			return "...";
		}

		static std::string for_null(const std::uint8_t *) {
			return "null";
		}
		
		static std::string for_bool(const std::uint8_t *) {
			return "bool";
		}
		
		static std::string for_char(const std::uint8_t *) {
			return "char";
		}

		static std::string for_int(const std::uint8_t *) {
			return "int";
		}

		static std::string for_float(const std::uint8_t *) {
			return "float";
		}

		static std::string for_string(const std::uint8_t *) {
			return "string";
		}

		static std::string for_array(const std::uint8_t * code) {
			return "array(" + type_name(std::next(code)) + ")";
		}

		static std::string for_tuple(const std::uint8_t *) {
			return "tuple";
		}

		static std::string for_tuple_n(const std::uint8_t * code) {
			std::ostringstream oss;
			oss << "tuple(";
			decode_tuple(code, [&] (auto * elem) { oss << type_name(elem); });
			oss << ")";
			return oss.str();
		}

		static std::string for_fx(const std::uint8_t *) {
			return "fx";
		}

		static std::string for_fx_n(const std::uint8_t * code) {
			std::ostringstream oss;
			oss << "fx(" << size_uint_8(code) << ")";
			return oss.str();
		}

		static std::string for_istream(const std::uint8_t *) {
			return "istream";
		}

		static std::string for_ostream(const std::uint8_t *) {
			return "ostream";
		}

		static std::string for_iter(const std::uint8_t *) {
			return "iter";
		}

		static std::string for_stop(const std::uint8_t *) {
			return "stop";
		}

		static std::string for_rng(const std::uint8_t *) {
			return "rng";
		}

		static std::string for_clock(const std::uint8_t *) {
			return "clock";
		}

		static std::string for_type(const std::uint8_t *) {
			return "type";
		}

		static std::string for_queue(const std::uint8_t * code) {
			return "queue(" + type_name(std::next(code)) + ")";
		}

		static std::string for_stack(const std::uint8_t * code) {
			return "stack(" + type_name(std::next(code)) + ")";
		}

		static std::string for_map(const std::uint8_t * code) {
			std::ostringstream oss;
			oss << "map(";
			oss << type_name(++code); 
			oss << ", "; 
			oss << type_name(++code); 
			oss << ")"; 
			return oss.str();
		}

		static std::string for_default(const std::uint8_t *) {
			throw except::invalid_argument("Cannot generate type name");
		}
	};



	std::string type_name(const std::uint8_t * code) {
		return decode_type<TypeName>(code);
	}



	std::string type_name(const Type & type) {
		return type_name(type.code.data());	
	}
}