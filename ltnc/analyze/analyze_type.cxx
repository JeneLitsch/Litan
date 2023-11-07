#include "analyze.hxx"
#include "ltn/type_code.hxx"
#include "stdxx/array.hxx"
#include "ltnc/sst/expr/Type.hxx"

namespace ltn::c {
	namespace {
		std::vector<std::uint8_t> analyze_type(const ast::Type & type, Scope & scope);
		
		
		std::vector<std::uint8_t> wrap_type(
			std::vector<std::uint8_t> type,
			std::uint8_t wrapper_type) {
			
			std::vector<std::uint8_t> arr{wrapper_type};
			arr += type;
			return arr;
		}

		
		
		std::vector<std::uint8_t> optional_subtype(
			std::uint8_t warpper_type,
			const auto & type,
			Scope & scope) {
			
			if(type.contains) {
				auto sub_type = analyze_type(*type.contains, scope);
				return wrap_type(std::move(sub_type), warpper_type);
			}
			else {
				return wrap_type({type_code::ANY}, warpper_type);
			}
		}



		std::array<std::uint8_t, 8> uint64_to_bytes(std::uint64_t num) {
			std::array<std::uint8_t, 8> bytes;
			for(std::size_t i = 0; i < 8; ++i) {
				bytes[i] = (num >> ((i) * 8)) & 0xff;
			}
			return bytes;
		}




		std::vector<std::uint8_t> analyze_type(const ast::Type::Null &, Scope &) {
			return {type_code::NVLL};		
		}

		std::vector<std::uint8_t> analyze_type(const ast::Type::Any &, Scope &) {
			return {type_code::ANY};		
		}

		std::vector<std::uint8_t> analyze_type(const ast::Type::Bool &, Scope &) {
			return {type_code::BOOL};		
		}

		std::vector<std::uint8_t> analyze_type(const ast::Type::Char &, Scope &) {
			return {type_code::CHAR};		
		}

		std::vector<std::uint8_t> analyze_type(const ast::Type::Int &, Scope &) {
			return {type_code::INT};		
		}

		std::vector<std::uint8_t> analyze_type(const ast::Type::Float &, Scope &) {
			return {type_code::FLOAT};		
		}

		std::vector<std::uint8_t> analyze_type(const ast::Type::String &, Scope &) {
			return {type_code::STRING};		
		}

		std::vector<std::uint8_t> analyze_type(const ast::Type::Array & type, Scope & scope) {
			return optional_subtype(type_code::ARRAY, type, scope);
		}

		std::vector<std::uint8_t> analyze_type(const ast::Type::Tuple &, Scope &) {
			return {type_code::TUPLE};		
		}

		std::vector<std::uint8_t> analyze_type(const ast::Type::TupleN & type, Scope & scope) {
			std::vector<std::uint8_t> code;
			code.push_back(type_code::TUPLE_N);
			std::uint64_t size = std::size(type.contains);
			code += uint64_to_bytes(size);
			for(const auto & elem : type.contains) {
				code += analyze_type(*elem, scope);
			}
			return code;
		}

		std::vector<std::uint8_t> analyze_type(const ast::Type::Fx &, Scope &) {
			return {type_code::FX};		
		}

		std::vector<std::uint8_t> analyze_type(const ast::Type::FxN & type, Scope &) {
			std::vector<std::uint8_t> code;
			code.push_back(type_code::FX_N);
			code += uint64_to_bytes(type.arity);
			return code;
		}

		std::vector<std::uint8_t> analyze_type(const ast::Type::IStream &, Scope &) {
			return {type_code::ISTREAM};
		}

		std::vector<std::uint8_t> analyze_type(const ast::Type::OStream &, Scope &) {
			return {type_code::OSTREAM};
		}

		std::vector<std::uint8_t> analyze_type(const ast::Type::Iterator &, Scope &) {
			return {type_code::ITERATOR};
		}

		std::vector<std::uint8_t> analyze_type(const ast::Type::IteratorStop &, Scope &) {
			return {type_code::ITERATOR_STOP};
		}

		std::vector<std::uint8_t> analyze_type(const ast::Type::Clock &, Scope &) {
			return {type_code::CLOCK};
		}

		std::vector<std::uint8_t> analyze_type(const ast::Type::Rng &, Scope &) {
			return {type_code::RNG};
		}

		std::vector<std::uint8_t> analyze_type(const ast::Type::TypeT &, Scope &) {
			return {type_code::TYPE};
		}

		std::vector<std::uint8_t> analyze_type(const ast::Type::Queue & type, Scope & scope) {
			return optional_subtype(type_code::QUEUE, type, scope);
		}

		std::vector<std::uint8_t> analyze_type(const ast::Type::Stack & type, Scope & scope) {
			return optional_subtype(type_code::STACK, type, scope);
		}

		std::vector<std::uint8_t> analyze_type(const ast::Type::Map & type, Scope & scope) {
			std::vector<std::uint8_t> code{type_code::MAP};
			static const std::vector<std::uint8_t> any{type_code::ANY};
			auto key = type.key ? analyze_type(*type.key, scope) : any;
			auto val = type.value ? analyze_type(*type.value, scope) : any;
			code += key;
			code += val;
			return code;
		}

		std::vector<std::uint8_t> analyze_type(const ast::Type::Struct & type, Scope & scope) {
			std::vector<std::uint8_t> code;
			code.push_back(type_code::STRUCT);
			code += uint64_to_bytes(std::size(type.members));
			for(auto & member : type.members) {
				code += uint64_to_bytes(scope.resolve_member_id(member.name));
				code += analyze_type(*member.type, scope);
			}
			return code;
		}

		std::vector<std::uint8_t> analyze_type(const ast::Type & type, Scope & scope) {
			return std::visit([&] (auto & t) {
				return analyze_type(t, scope);
			}, type.variant);
		}
	}



	sst::expr_ptr analyze_expr(const ast::Type & type, Scope & scope) {
		return std::make_unique<sst::Type>(analyze_type(type, scope));
	}
}