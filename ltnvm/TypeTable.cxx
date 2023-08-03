#include "TypeTable.hxx"
#include "ltnvm/utils/type_check.hxx"
#include "ltnvm/utils/convert.hxx"
#include "ltnvm/utils/cast.hxx"
#include "ltnvm/VmCore.hxx"
#include "ltn/type_code.hxx"
#include "stdxx/string_literal.hxx"

namespace ltn::vm {
	namespace {
		using TypeResult = std::pair<std::uint64_t, const std::uint8_t*>;
		
		TypeResult make_type(TypeTable & type_table, const std::uint8_t * code);
		
		inline std::uint64_t read_uint_64(const std::uint8_t * code) {
			std::uint64_t size = 0;
			for(std::size_t i = 0; i < 8; ++i) {
				size += static_cast<std::uint64_t>(*(code++)) << (i * 8);
			}
			return size;
		}



		template<typename Node>
		std::uint64_t get_type(TypeTable & type_table, auto & bytes, auto && ... args) {
			if(type_table.contains(bytes)) {
				return type_table.resolve(bytes);
			} 
			else {
				auto node = std::make_unique<Node>(std::move(args)...);
				return type_table.add(bytes, std::move(node));
			}
		}



		template<stx::string_literal NAME, auto IS, auto CAST>
		class PrimaryType : public Type {
		public:
			virtual bool is(const Value & value, VmCore & core) const override {
				return IS(value, core);
			}

			virtual Value cast(const Value & value, VmCore & core) const override {
				return CAST(value, core);
			}

			virtual std::string name(VmCore &) const override {
				return NAME.str();
			}

			static TypeResult make(TypeTable & type_table, const std::uint8_t * code) {
				auto end = code + 1;
				std::vector<std::uint8_t> bytes {code, end}; 
				return { get_type<PrimaryType>(type_table, bytes), end };
			}
		};



		template<stx::string_literal NAME, auto IS, auto CAST>
		class UnaryType : public Type {
		public:
			UnaryType(const Type * sub_type) : sub_type{sub_type} {}

			virtual bool is(const Value & value, VmCore & core) const override {
				return IS(value, core, sub_type);
			}

			virtual Value cast(const Value & value, VmCore & core) const override {
				return CAST(value, core, sub_type);
			}

			virtual std::string name(VmCore & core) const override {
				return NAME.str() + "(" + sub_type->name(core) + ")";
			}

			static TypeResult make(TypeTable & type_table, const std::uint8_t * code) {
				auto [sub_node, end] = make_type(type_table, code + 1);
				std::vector<std::uint8_t> bytes {code, end}; 
				return { get_type<UnaryType>(type_table, bytes, type_table[sub_node]), end };
			}

		private:
			const Type * sub_type;
		};



		template<stx::string_literal NAME, auto IS, auto CAST>
		class BinaryType : public Type {
		public:
			BinaryType(
				const Type * sub_type_l,
				const Type * sub_type_r)
				: sub_type_l{sub_type_l}
				, sub_type_r{sub_type_r} {}

			virtual bool is(const Value & value, VmCore & core) const override {
				return IS(value, core, sub_type_l, sub_type_r);
			}

			virtual Value cast(const Value & value, VmCore & core) const override {
				return CAST(value, core, sub_type_l, sub_type_r);
			}

			virtual std::string name(VmCore & core) const override {
				return NAME.str() + "(" + sub_type_l->name(core) + "," + sub_type_r->name(core) + ")";
			}

			static TypeResult make(TypeTable & type_table, const std::uint8_t * code) {
				auto [sub_node_l, mid] = make_type(type_table, code + 1);
				auto [sub_node_r, end] = make_type(type_table, mid);
				std::vector<std::uint8_t> bytes {code, end}; 
				return { get_type<BinaryType>(type_table, bytes, type_table[sub_node_l], type_table[sub_node_r]), end };
			}

		private:
			const Type * sub_type_l;
			const Type * sub_type_r;
		};



		template<stx::string_literal NAME, auto IS, auto CAST>
		class NAryType : public Type {
		public:
			NAryType(std::vector<const Type *> sub_types)
				: sub_types{std::move(sub_types)} {}

			virtual bool is(const Value & value, VmCore & core) const override {
				return IS(value, core, sub_types);
			}

			virtual Value cast(const Value & value, VmCore & core) const override {
				return CAST(value, core, sub_types);
			}

			virtual std::string name(VmCore & core) const override {
				std::ostringstream oss;
				oss << NAME.str() << "(";
				bool first = true;
				for(const auto & st : this->sub_types) {
				 	if(first) first = false;
					else oss << ",";
					oss << st->name(core);
				}
				oss << ")";
				return oss.str();
			}

			static TypeResult make(TypeTable & type_table, const std::uint8_t * code) {
				auto number = read_uint_64(code + 1);
				std::vector<const Type *> sub_types;
				auto current = code + 1 + 8;
				for(std::size_t i = 0; i < number; ++i) {
					auto [node, next] = make_type(type_table, current);
					current = next;
					sub_types.push_back(type_table[node]);
				}
				auto end = current;
				std::vector<std::uint8_t> bytes {code, end}; 
				return { get_type<NAryType>(type_table, bytes, sub_types), end };
			}

		private:
			std::vector<const Type *> sub_types;
		};



		template<stx::string_literal NAME, auto IS, auto CAST>
		class NumericType : public Type {
		public:
			NumericType(std::uint64_t number) : number{number} {}

			virtual bool is(const Value & value, VmCore & core) const override {
				return IS(value, core, number);
			}

			virtual Value cast(const Value & value, VmCore & core) const override {
				return CAST(value, core, number);
			}

			virtual std::string name(VmCore &) const override {
				std::ostringstream oss;
				oss << NAME.str() << "(" << number << ")";
				return oss.str();
			}

			static TypeResult make(TypeTable & type_table, const std::uint8_t * code) {
				auto end = code + 1 + 8;
				std::vector<std::uint8_t> bytes {code, end}; 
				auto number = read_uint_64(code + 1);
				return { get_type<NumericType>(type_table, bytes, number), end };
			}

		private:
			std::uint64_t number;
		};



		class StructType : public Type {
		public:
			struct Member {
				std::uint64_t member_id;
				const Type * type;
			};
			StructType(std::vector<Member> members) : members{std::move(members)} {}

			virtual bool is(const Value & value, VmCore & core) const override {
				if(!is_struct(value)) return false;
				auto & strukt = core.heap.read<Struct>(value);
				for(auto & type_member : this->members) {
					if(auto * data_member = strukt.get(type_member.member_id)){
						if(!type_member.type->is(*data_member, core)) {
							return false;
						}
					}
					else {
						return false;
					}
				} 
				return true;
			}

			virtual Value cast(const Value & value, VmCore & core) const override {
				return this->is(value, core) ? value : value::null;
			}

			virtual std::string name(VmCore & core) const override {
				std::ostringstream oss;
				oss << "struct";
				if(!std::empty(this->members)) {
					oss << "(";
					bool first = true; 
					for(auto & member : this->members) {
						if(first) first = false;
						else oss << ",";
						oss << ".";
						oss << core.member_name_table.at(member.member_id);
						oss << ":";
						oss << member.type->name(core);
					}
					oss << ")";
				}
				return oss.str();
			}

			static TypeResult make(TypeTable & type_table, const std::uint8_t * code) {
				auto begin = code;
				std::vector<Member> members;
				++code;
				auto size = read_uint_64(code);
				code += 8;

				for(std::size_t i = 0; i < size; ++i) {
					auto id = read_uint_64(code);
					auto [type, next] = make_type(type_table, code + 8);
					code = next;

					members.push_back(Member{
						.member_id = id,
						.type = type_table[type],
					});
				}
				
				std::vector<std::uint8_t> bytes {begin, code}; 

				return { get_type<StructType>(type_table, bytes, std::move(members)), code };
			}

		private:
			std::vector<Member> members;
		};



		template<auto IS>
		bool simple_check_for(const Value & value, VmCore &) {
			return IS(value);
		}


		
		template<auto IS>
		Value ret_if_or_null(const Value & value, VmCore &) {
			return IS(value) ? value : value::null;
		}



		Value no_cast(const Value & value, VmCore &) {
			return value;
		}



		bool always_true(const Value &, VmCore &) {
			return true;
		}



		Value type_cast_null(const Value &, VmCore &) {
			return value::null;
		}



		Value type_cast_bool(const Value & value, VmCore & core) {
			return value::boolean(cast::to_bool(value, core));
		}


		
		Value type_cast_char(const Value & value, VmCore &) {
			return value::character(cast::to_char(value));
		}



		Value type_cast_int(const Value & value, VmCore &) {
			return value::integer(cast::to_int(value));
		}



		Value type_cast_float(const Value & value, VmCore & core) {
			return value::floating(cast::to_float(value, core.heap));
		}



		Value type_cast_string(const Value & value, VmCore & core) {
			return value::string(core.heap.alloc(String{cast::to_string(value, core.heap)}));
		}



		template<typename Data, auto make_value, auto check_type>
		Value cast_unary_type(const Value & value, VmCore & core, const Type * sub_type) {
			if(!check_type(value)) return value::null;
			const Data & input = core.heap.read<Data>(value); 
			Data output;
			for(const auto & elem : input.data) {
				output.data.push_back(sub_type->cast(elem, core));
			}
			return make_value(core.heap.alloc(std::move(output)));
		}



		template<typename Data, auto check_type>
		bool is_unary_type(const Value & value, VmCore & core, const Type * sub_type) {
			if(!check_type(value)) return false;
			const Data & input = core.heap.read<Data>(value);
			return std::all_of(std::begin(input.data), std::end(input.data), 
				[&](const auto & elem) { return sub_type->is(elem, core); 
			});
		}



		bool type_is_fx_n(const Value & value, VmCore & core, std::uint64_t arity) {
			if(!is_fxptr(value)) return false;
			const FxPointer & input = core.heap.read<FxPointer>(value);
			return input.params == arity;
		}



		Value type_cast_fx_n(const Value & value, VmCore & core, std::uint64_t arity) {
			return type_is_fx_n(value, core, arity) ? value : value::null; 
		}



		bool type_is_map(const Value & value, VmCore & core, const Type * sub_type_l, const Type * sub_type_r) {
			if(!is_map(value)) return false;
			const Map & input = core.heap.read<Map>(value);
			return std::all_of(std::begin(input), std::end(input), 
				[&](const auto & elem) {
					auto & [key, val] = elem;
					return sub_type_l->is(key, core) && sub_type_r->is(val, core); 
				}
			);
		}



		Value type_cast_map(const Value & value, VmCore & core, const Type * sub_type_l, const Type * sub_type_r) {
			return type_is_map(value, core, sub_type_l, sub_type_r) 
				? value
				: value::null; 
		}



		Value type_cast_tuple_n(const Value & value, VmCore & core, const std::vector<const Type *> & sub_types) {
			if(is_contiguous(value)) {
				const Contiguous & input = core.heap.read<Contiguous>(value);
				if(std::size(input.data) != std::size(sub_types)) return value::null;
				Tuple output;
				for(std::size_t i = 0; i < std::size(input.data); ++i) {
					output.push_back(sub_types[i]->cast(input.data[i], core));
				}
				return value::tuple(core.heap.alloc(std::move(output)));
			}
			else {
				return value::null;
			}
		}



		bool type_is_tuple_n(const Value & value, VmCore & core, const std::vector<const Type *> & sub_types) {
			if(!is_tuple(value)) return false;
			const Tuple & input = core.heap.read<Tuple>(value);
			if(std::size(input.data) != std::size(sub_types)) return false;
			for(std::size_t i = 0; i < std::size(input.data); ++i) {
				if(!sub_types[i]->is(input.data[i], core)) return false;
			}
			return true;
		}



		using TypeAny = PrimaryType<"any"
			, always_true
			, no_cast
		>;
		
		using TypeNull = PrimaryType<"null"
			, simple_check_for<is_null>
			, type_cast_null
		>;

		using TypeBool = PrimaryType<"bool"
			, simple_check_for<is_bool>
			, type_cast_bool
		>;

		using TypeChar = PrimaryType<"char"
			, simple_check_for<is_char>
			, type_cast_char
		>;

		using TypeInt = PrimaryType<"int"
			, simple_check_for<is_int>
			, type_cast_int
		>;

		using TypeFloat = PrimaryType<"float"
			, simple_check_for<is_float>
			, type_cast_float
		>;

		using TypeString = PrimaryType<"string"
			, simple_check_for<is_string>
			, type_cast_string
		>;

		using TypeArray = UnaryType<"array"
			, is_unary_type<Array, is_array>
			, cast_unary_type<Array, value::array, is_array>
		>;

		using TypeTuple = PrimaryType<"tuple"
			, simple_check_for<is_tuple>
			, ret_if_or_null<is_tuple>
		>;

		using TypeTupleN = NAryType<"tuple"
			, type_is_tuple_n
			, type_cast_tuple_n
		>;

		using TypeFx = PrimaryType<"fx"
			, simple_check_for<is_fxptr>
			, ret_if_or_null<is_fxptr>
		>;    

		using TypeFxN = NumericType<"fx"
			, type_is_fx_n
			, type_cast_fx_n
		>;

		using TypeIstream = PrimaryType<"istream"
			, simple_check_for<is_istream>
			, ret_if_or_null<is_istream>
		>;

		using TypeOstream = PrimaryType<"ostream"
			, simple_check_for<is_ostream>
			, ret_if_or_null<is_ostream>
		>;

		using TypeIter = PrimaryType<"iter"
			, simple_check_for<is_iterator>
			, ret_if_or_null<is_iterator>
		>; 

		using TypeStop = PrimaryType<"stop"
			, simple_check_for<is_iterator_stop>
			, ret_if_or_null<is_iterator_stop>
		>; 

		using TypeRng = PrimaryType<"rng"
			, simple_check_for<is_rng>
			, ret_if_or_null<is_rng>
		>;

		using TypeClock = PrimaryType<"clock"
			, simple_check_for<is_clock>
			, ret_if_or_null<is_clock>
		>;

		using TypeType = PrimaryType<"type"
			, simple_check_for<is_type>
			, ret_if_or_null<is_type>
		>;

		using TypeQueue = UnaryType<"queue"
			, is_unary_type<Queue, is_queue>
			, cast_unary_type<Queue, value::queue, is_queue>
		>;

		using TypeVmStack = UnaryType<"stack"
			, is_unary_type<Stack, is_stack>
			, cast_unary_type<Stack, value::stack, is_stack>
		>;

		using TypeMap = BinaryType<"map"
			, type_is_map
			, type_cast_map
		>;

		using TypeStruct = StructType;



		TypeResult make_type(TypeTable & type_table, const std::uint8_t * code) {
			switch (*code) {
				case type_code::ANY: return TypeAny::make(type_table, code);
				case type_code::NVLL: return TypeNull::make(type_table, code);
				case type_code::BOOL: return TypeBool::make(type_table, code);
				case type_code::CHAR: return TypeChar::make(type_table, code);
				case type_code::INT: return TypeInt::make(type_table, code);
				case type_code::FLOAT: return TypeFloat::make(type_table, code);
				case type_code::STRING: return TypeString::make(type_table, code);
				case type_code::ARRAY: return TypeArray::make(type_table, code);
				case type_code::TUPLE: return TypeTuple::make(type_table, code);
				case type_code::TUPLE_N: return TypeTupleN::make(type_table, code);
				case type_code::FX: return TypeFx::make(type_table, code);
				case type_code::FX_N: return TypeFxN::make(type_table, code);
				case type_code::ISTREAM: return TypeIstream::make(type_table, code);
				case type_code::OSTREAM: return TypeOstream::make(type_table, code);
				case type_code::ITERATOR: return TypeIter::make(type_table, code);
				case type_code::ITERATOR_STOP: return TypeStop::make(type_table, code);
				case type_code::RNG: return TypeRng::make(type_table, code);
				case type_code::CLOCK: return TypeClock::make(type_table, code);
				case type_code::TYPE: return TypeType::make(type_table, code);
				case type_code::QUEUE: return TypeQueue::make(type_table, code);
				case type_code::STACK: return TypeVmStack::make(type_table, code);
				case type_code::MAP: return TypeMap::make(type_table, code);
				case type_code::STRUCT: return TypeStruct::make(type_table, code);
				default: throw std::runtime_error{""};
			}
		}
	}



	std::pair<std::uint64_t, const std::uint8_t *> TypeTable::make(const std::uint8_t * code) {
		return make_type(*this, code);
	}



	const Type * TypeTable::operator[](std::uint64_t id) const {
		return this->types[id].get();
	}



	std::uint64_t TypeTable::add(const std::vector<std::uint8_t> & code, std::unique_ptr<Type> type) {
		std::uint64_t id = std::size(types);
		this->code_to_id.insert({code, id});
		this->types.push_back(std::move(type));
		return id;
	}



	bool TypeTable::contains(const std::vector<std::uint8_t> & code) const {
		return this->code_to_id.contains(code);
	}


		
	std::uint64_t TypeTable::resolve(const std::vector<std::uint8_t> & code) const {
		return this->code_to_id.at(code);
	}
}