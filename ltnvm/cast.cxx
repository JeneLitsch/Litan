#include "cast.hxx"
#include "type_check.hxx"
#include "Exception.hxx"
#include "convert.hxx"
#include "ltn/float64_t.hxx"

namespace ltn::vm::cast {
	namespace {
		template<typename To>
		To parse_value(const std::string & str) {
			To to;
			std::stringstream ss{str};
			ss >> to;
			if(ss.fail()) {
				throw except::invalid_argument("Cannot parse string to value");
			}
			return to;
		}
	}

	namespace {
		auto print_element(const Value value, Heap & heap) {
			return cast::to_string(value, heap);
		} 

		auto print_element(const std::pair<Value, Value> pair, Heap & heap) {
			std::ostringstream ss;
			const auto & [key, val] = pair;
			ss << to_string(key, heap) << " : " << to_string(val, heap);
			return ss.str();
		}

		template<typename Iterator>
		void print_all(
			Iterator begin,
			Iterator end,
			std::ostream & out,
			Heap & heap,
			char open = '[',
			char close = ']') {
			
			out << open;
			for(auto it = begin; it != end; ++it) {
				if (it != begin) out << ", ";
				out << print_element(*it, heap);
			}
			out << close;
		}
	}



	std::string to_string(Value value, Heap & heap) {
		if(is_null(value)) {
			return "null";
		}
		if(is_bool(value)) {
			std::stringstream ss;
			ss << std::boolalpha << value.b;
			return ss.str();
		}

		if(is_char(value)) {
			return std::string(1, value.c);
		}

		if(is_int(value)) {
			std::stringstream ss;
			ss << value.i;
			return ss.str();
		}

		if(is_float(value)) {
			std::stringstream ss;
			ss << value.f;
			return ss.str();
		}


		if(is_array(value)) {
			const auto & array = heap.read<Array>(value.u).get();
			std::stringstream ss;
			print_all(std::begin(array), std::end(array), ss, heap);
			return ss.str();
		}

		if(is_range(value)) {
			const auto & range = heap.read<Range>(value.u);
			const auto & array = heap.read<Array>(range.array).get();
			auto begin = std::begin(array) + range.begin;
			auto end = std::begin(array) + range.end;
			std::stringstream ss;
			print_all(begin, end, ss, heap);
			return ss.str();
		}

		if(is_ostream(value)) {
			const auto & out = heap.read<OStream>(value.u);
			if(out.oss) {
				return out.oss->str();
			}
			return "<ostream>";
		}

		if(is_istream(value)) {
			return "<istream>";
		}

		if(is_fxptr(value)) {
			const auto & fxptr = heap.read<FxPointer>(value.u);
			std::ostringstream ss;
			ss << "<fx:";
			ss << fxptr.address << "," << fxptr.params << ">";
			return  ss.str();
		}

		if(is_clock(value)) {
			const auto & clock = heap.read<Clock>(value.u);
			std::ostringstream ss;
			ss << "<clock: " << clock.getSeconds() << "s>";
			return ss.str();
		}

		if(is_struct(value)) {
			return "<struct>";
		}

		if(is_queue(value)) {
			const auto & deque = heap.read<Deque>(value.u).get();
			std::ostringstream ss;
			print_all(std::begin(deque), std::end(deque), ss, heap, '<', '>');
			return ss.str();
		}

		if(is_stack(value)) {
			const auto & deque = heap.read<Deque>(value.u).get();
			std::ostringstream ss;
			print_all(std::begin(deque), std::end(deque), ss, heap, '<', '>');
			return ss.str();
		}

		if(is_map(value)) {
			const auto & map = heap.read<Map>(value.u).get();
			std::ostringstream ss;
			print_all(std::begin(map), std::end(map), ss, heap, '{', '}');
			return ss.str();
		}

		if(is_rng(value)) {
			return "<RandomEngine>";
		}

		return convert::to_string(value, heap);
	}


	std::vector<Value> to_array(Value value) {
		return {value};
	}

	std::int64_t to_int(Value value, Heap & heap) {
		if(is_float(value)) {
			return static_cast<std::int64_t>(value.f);
		}
		
		if(is_string(value)) {
			const auto & str = heap.read<String>(value.u);
			return parse_value<std::int64_t>(str.str); 
		}

		return convert::to_int(value);
	}



	stx::float64_t to_float(Value value, Heap & heap) {
		if(is_string(value)) {
			const auto & str = heap.read<String>(value.u);
			return parse_value<stx::float64_t>(str.str); 
		}
		
		if (is_clock(value)) {
			const auto & clock = heap.read<Clock>(value.u);
			return clock.getSeconds();
		}

		return convert::to_float(value);
	}


	bool to_bool(Value value) {
		return convert::to_bool(value);
	}

	char to_char(Value value) {
		if(is_int(value)) {
			return static_cast<char>(value.i);
		}

		if(is_float(value)) {
			return static_cast<char>(value.f);
		}

		return convert::to_char(value);
	}
}