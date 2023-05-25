#include "stringify.hxx"
#include "Exception.hxx"
#include "ltnvm/call_special_member.hxx"
#include "ltnvm/LtnVM.hxx"

namespace ltn::vm {
	namespace {
		auto print_element(const Value value, VmCore & core) {
			return stringify(value, core);
		} 

		auto print_element(const std::pair<Value, Value> pair, VmCore & core) {
			std::ostringstream ss;
			const auto & [key, val] = pair;
			ss << stringify(key, core) << " : " << stringify(val, core);
			return ss.str();
		}

		template<typename Iterator>
		void print_all(
			Iterator begin,
			Iterator end,
			std::ostream & out,
			VmCore & core,
			char open = '[',
			char close = ']') {
			
			out << open;
			for(auto it = begin; it != end; ++it) {
				if (it != begin) out << ", ";
				out << print_element(*it, core);
			}
			out << close;
		}
	}


	




	std::string stringify(const Value & value, VmCore & core) {
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
			const auto & array = core.heap.read<Array>(value.u);
			std::stringstream ss;
			print_all(std::begin(array), std::end(array), ss, core, '[', ']');
			return ss.str();
		}

		if(is_tuple(value)) {
			const auto & array = core.heap.read<Array>(value.u);
			std::stringstream ss;
			print_all(std::begin(array), std::end(array), ss, core, '(', ')');
			return ss.str();
		}

		if(is_ostream(value)) {
			const auto & out = core.heap.read<OStream>(value.u);
			if(out.oss) {
				return out.oss->str();
			}
			return "<ostream>";
		}

		if(is_istream(value)) {
			return "<istream>";
		}

		if(is_fxptr(value)) {
			std::ostringstream ss;
			ss << "<function>";
			return  ss.str();
		}

		if(is_clock(value)) {
			const auto & clock = core.heap.read<Clock>(value.u);
			std::ostringstream ss;
			ss << "<clock: " << clock.getSeconds() << "s>";
			return ss.str();
		}

		if(is_struct(value)) {
			try {
				auto result = call_special_member<MemberCode::STR>(core, value);
				if(is_string(result)) {
					return core.heap.read<String>(result);
				} 
			}
			catch(...) {
				return "<struct>";
			}
			throw except::invalid_argument("Special member {str} must return string");
		}

		if(is_queue(value)) {
			const auto & deque = core.heap.read<Deque>(value.u);
			std::ostringstream ss;
			print_all(std::begin(deque), std::end(deque), ss, core, '<', '>');
			return ss.str();
		}

		if(is_stack(value)) {
			const auto & deque = core.heap.read<Deque>(value.u);
			std::ostringstream ss;
			print_all(std::begin(deque), std::end(deque), ss, core, '<', '>');
			return ss.str();
		}

		if(is_map(value)) {
			const auto & map = core.heap.read<Map>(value.u);
			std::ostringstream ss;
			print_all(std::begin(map), std::end(map), ss, core, '{', '}');
			return ss.str();
		}

		if(is_rng(value)) {
			return "<RNG>";
		}

		if(is_string(value)) {
			return core.heap.read<String>(value.u);
		}

		if(is_iterator(value)) {
			return "<iterator>";
		}

		if(is_iterator_stop(value)) {
			return "<iterator_stop>";
		}

		if(is_type(value)) {
			auto & type = *core.types[value.u];
			return type.name();
		}

		throw Exception{
			.type = Exception::Type::INVALID_ARGUMENT,
			.msg = "Cannot stringify"
		};
	}
}