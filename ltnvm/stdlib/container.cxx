#include "container.hxx"

#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/type_check.hxx"
#include "ltnvm/native/native.hxx"
#include "ltnvm/objects/iter.hxx"

#include "array.hxx"
#include "tuple.hxx"
#include "string.hxx"
#include "queue.hxx"
#include "stack.hxx"
#include "map.hxx"

namespace ltn::vm::stdlib {
	Value size::func(Context * context, const Value * args) {
		if(is_array(args[0]))    return stdlib::array_size::func(context, args);
		if(is_tuple(args[0]))    return stdlib::tuple_size::func(context, args);
		if(is_string(args[0]))   return stdlib::string_size::func(context, args);
		if(is_queue(args[0]))    return stdlib::queue_size::func(context, args);
		if(is_stack(args[0]))    return stdlib::stack_size::func(context, args);
		if(is_map(args[0]))      return stdlib::map_size::func(context, args);
		if(is_iterator(args[0])) return value::integer(iterator::size(args[0]));
		throw except::invalid_argument();
	}



	Value is_empty::func(Context * context, const Value * args) {
		return value::boolean(size::func(context, args).i == 0);
	}



	Value front::func(Context * context, const Value * args) {
		if(is_array(args[0]))    return stdlib::array_front::func(context, args);
		if(is_tuple(args[0]))    return stdlib::tuple_front::func(context, args);
		if (is_string(args[0])) {
			const String * str = value::as<String>(args[0]);
			if(std::empty(*str)) throw except::out_of_range();
			return value::integer(str->front());
		}
		throw except::invalid_argument();
	}



	Value back::func(Context * context, const Value * args) {
		if(is_array(args[0]))    return stdlib::array_back::func(context, args);
		if(is_tuple(args[0]))    return stdlib::tuple_back::func(context, args);
		if (is_string(args[0])) {
			const String * str = value::as<String>(args[0]);
			if(std::empty(*str)) throw except::out_of_range();
			return value::integer(str->back());
		}
		throw except::invalid_argument();
	}


	Value push::func(Context * context, const Value * args) {
		if(is_array(args[0])) return stdlib::array_push::func(context, args);
		if(is_stack(args[0])) return stdlib::stack_push::func(context, args);
		if(is_queue(args[0])) return stdlib::queue_push::func(context, args);
		throw except::invalid_argument();
	}


	Value pop::func(Context * context, const Value * args) {
		if(is_array(args[0])) return stdlib::array_pop::func(context, args);
		if(is_stack(args[0])) return stdlib::stack_pop::func(context, args);
		if(is_queue(args[0])) return stdlib::queue_pop::func(context, args);
		throw except::invalid_argument();
	}


	Value peek::func(Context * context, const Value * args) {
		if(is_array(args[0])) return stdlib::array_peek::func(context, args);
		if(is_string(args[0])) {
			String * container = value::as<String>(args[0]);
			if(std::empty(*container)) throw except::out_of_range();
			const auto elem = container->unsafe_back();
			return value::integer(elem);
		}
		if(is_stack(args[0])) {
			Stack * container = value::as<Stack>(args[0]);
			if(std::empty(*container)) throw except::out_of_range();
			const auto elem = container->unsafe_back();
			return elem;
		}

		if(is_queue(args[0])) {
			Segmented * container = value::as<Segmented>(args[0]);
			if(std::empty(*container)) throw except::out_of_range();
			const auto elem = container->unsafe_front();
			return elem;
		}
		throw except::invalid_argument();
	}


	
	Value has::func(Context * context, const Value * args) {
		if(is_map(args[0]))   return stdlib::map_has::func(context, args);
		if(is_array(args[0])) return stdlib::array_has::func(context, args);
		throw except::invalid_argument();
	}



	Value insert::func(Context * context, const Value * args) {
		if(is_array(args[0])) return array_insert::func(context, args);
		if(is_map(args[0]))   return map_insert::func(context, args);
		throw except::invalid_argument();
	}



	Value insert_front::func(Context * context, const Value * args) {
		if(is_array(args[0])) {
			Array * arr = value::as<Array>(args[0]);
			arr->unsafe_insert(std::begin(*arr), args[1]);
			return value::null;
		} 

		throw except::invalid_argument();
	}



	Value insert_back::func(Context * context, const Value * args) {
		if(is_array(args[0])) return array_push::func(context, args);
		throw except::invalid_argument();
	}



	Value erase::func(Context * context, const Value * args) {
		if(is_array(args[0])) return array_erase::func(context, args);
		if(is_map(args[0]))   return map_erase::func(context, args);
		throw except::invalid_argument();
	}



	Value erase_front::func(Context *, const Value * args) {
		if(is_array(args[0])) return value::as<Array>(args[0])->erase(0);
		throw except::invalid_argument();
	}



	Value erase_back::func(Context *, const Value * args) {
		if(is_array(args[0])) return value::as<Array>(args[0])->pop_back();
		throw except::invalid_argument();
	}
}