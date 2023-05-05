#include "analyze.hxx"
#include "ltn/type_code.hxx"
#include "stdxx/array.hxx"

namespace ltn::c {
	namespace {
		std::vector<std::uint8_t> analyze_type(const ast::Type & type, Scope & scope);


		std::vector<std::uint8_t> analyze_type(const ast::Type::Null & type, Scope & scope) {
			return {type_code::NVLL};		
		}

		std::vector<std::uint8_t> analyze_type(const ast::Type::Bool & type, Scope & scope) {
			return {type_code::BOOL};		
		}

		std::vector<std::uint8_t> analyze_type(const ast::Type::Char & type, Scope & scope) {
			return {type_code::CHAR};		
		}

		std::vector<std::uint8_t> analyze_type(const ast::Type::Int & type, Scope & scope) {
			return {type_code::INT};		
		}

		std::vector<std::uint8_t> analyze_type(const ast::Type::Float & type, Scope & scope) {
			return {type_code::FLOAT};		
		}

		std::vector<std::uint8_t> analyze_type(const ast::Type::String & type, Scope & scope) {
			return {type_code::STRING};		
		}


		std::vector<std::uint8_t> array_of(std::vector<std::uint8_t> type) {
			std::vector<std::uint8_t> arr{type_code::ARRAY};
			arr += type;
			return arr;
		}
		
		std::vector<std::uint8_t> analyze_type(const ast::Type::Array & type, Scope & scope) {
			if(type.contains) {
				return array_of(analyze_type(*type.contains, scope));
			}
			else {
				return array_of({type_code::ANY});
			}
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