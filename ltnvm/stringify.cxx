#include "stringify.hxx"
#include "Exception.hxx"

namespace ltn::vm {
	namespace {
		auto print_element(const Value value, Heap & heap) {
			return stringify(value, heap);
		} 

		auto print_element(const std::pair<Value, Value> pair, Heap & heap) {
			std::ostringstream ss;
			const auto & [key, val] = pair;
			ss << stringify(key, heap) << " : " << stringify(val, heap);
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
	std::string stringify(const Value & value, Heap & heap) {
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
			const auto & array = heap.read<Array>(value.u);
			std::stringstream ss;
			print_all(std::begin(array), std::end(array), ss, heap, '[', ']');
			return ss.str();
		}

		if(is_tuple(value)) {
			const auto & array = heap.read<Array>(value.u);
			std::stringstream ss;
			print_all(std::begin(array), std::end(array), ss, heap, '(', ')');
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

		if(is_external(value)) {
			std::ostringstream ss;
			ss << "<external:" << value.u << ">";
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
			const auto & deque = heap.read<Deque>(value.u);
			std::ostringstream ss;
			print_all(std::begin(deque), std::end(deque), ss, heap, '<', '>');
			return ss.str();
		}

		if(is_stack(value)) {
			const auto & deque = heap.read<Deque>(value.u);
			std::ostringstream ss;
			print_all(std::begin(deque), std::end(deque), ss, heap, '<', '>');
			return ss.str();
		}

		if(is_map(value)) {
			const auto & map = heap.read<Map>(value.u);
			std::ostringstream ss;
			print_all(std::begin(map), std::end(map), ss, heap, '{', '}');
			return ss.str();
		}

		if(is_rng(value)) {
			return "<RNG>";
		}

		if(is_string(value)) {
			return heap.read<String>(value.u);
		}

		throw Exception{
			.type = Exception::Type::INVALID_ARGUMENT,
			.msg = "Cannot stringify"
		};
	}
}