#include "stringify.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/special_member.hxx"
#include "ltnvm/VM.hxx"

namespace ltn::vm {
	namespace {
		auto print_element(const Value value, VMCore & core) {
			return stringify(value, core);
		} 

		auto print_element(const std::pair<Value, Value> pair, VMCore & core) {
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
			VMCore & core,
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


	




	std::string stringify(const Value & value, VMCore & core) {
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
			const auto & array = core.heap.read<Array>(value);
			std::stringstream ss;
			print_all(std::begin(array), std::end(array), ss, core, '[', ']');
			return ss.str();
		}

		if(is_tuple(value)) {
			const auto & tuple = core.heap.read<Tuple>(value);
			std::stringstream ss;
			print_all(std::begin(tuple), std::end(tuple), ss, core, '(', ')');
			return ss.str();
		}

		if(is_ostream(value)) {
			const auto & out = core.heap.read<OStream>(value);
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
			const auto & clock = core.heap.read<Clock>(value);
			std::ostringstream ss;
			ss << "<clock: " << clock.getSeconds() << "s>";
			return ss.str();
		}

		if(is_struct(value)) {
			auto & strukt = core.heap.read<Struct>(value);
			auto fx = find_special_member<MemberCode::OPERATOR_STR>(strukt);
			if(!fx) return "<struct>";
			auto result = run_special_member(core, *fx, value);
			if(is_string(result)) {
				return core.heap.read<String>(result).get_underlying();
			} 
			throw except::invalid_argument("Special member {str} must return string");
		}

		if(is_queue(value)) {
			const auto & deque = core.heap.read<Segmented>(value);
			std::ostringstream ss;
			print_all(std::begin(deque), std::end(deque), ss, core, '<', '>');
			return ss.str();
		}

		if(is_stack(value)) {
			const auto & deque = core.heap.read<Segmented>(value);
			std::ostringstream ss;
			print_all(std::begin(deque), std::end(deque), ss, core, '<', '>');
			return ss.str();
		}

		if(is_map(value)) {
			const auto & map = core.heap.read<Map>(value);
			std::ostringstream ss;
			if(map.empty()) ss << "[:]";
			else print_all(std::begin(map), std::end(map), ss, core, '[', ']');
			return ss.str();
		}

		if(is_rng(value)) {
			return "<RNG>";
		}

		if(is_string(value)) {
			return core.heap.read<String>(value).get_underlying();
		}

		if(is_iterator(value)) {
			return "<iterator>";
		}

		if(is_iterator_stop(value)) {
			return "<iterator_stop>";
		}

		if(is_type(value)) {
			return value.obj_type->name(core);
		}

		if(is_coroutine(value)) {
			const auto & coroutine = core.heap.read<Coroutine>(value);
			const auto & locals = coroutine.local_variables;
			std::ostringstream ss;
			ss << "<coroutine";
			print_all(std::begin(locals), std::end(locals), ss, core, '{', '}');
			ss << ">";
			return ss.str();
		}

		throw Exception{
			.type = Exception::Type::INVALID_ARGUMENT,
			.msg = "Cannot stringify"
		};
	}
}