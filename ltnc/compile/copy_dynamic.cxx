#include <sstream>
#include "stdxx/array.hxx"
#include "ltn/type_code.hxx"
#include "ltnc/compile/copy_dynamic.hxx"
#include "ltnc/compile/cast_utils.hxx"
#include "ltnc/type/check.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	namespace {
		std::vector<std::uint8_t> to_type_code(
			const type::Type &,
			const SourceLocation &);



		std::vector<std::uint8_t> cast_to(
			const type::Bool &,
			const SourceLocation &) {
			return { type_code::BOOL };
		}



		std::vector<std::uint8_t> cast_to(
			const type::Char &,
			const SourceLocation &) {
			
			return { type_code::CHAR };
		}



		std::vector<std::uint8_t> cast_to(
			const type::Int &,
			const SourceLocation &) {
			
			return { type_code::INT };
		}



		std::vector<std::uint8_t> cast_to(
			const type::Float &,
			const SourceLocation &) {
			
			return { type_code::FLOAT };
		}



		std::vector<std::uint8_t> cast_to(
			const type::String &,
			const SourceLocation &) {
			return { type_code::STRING };
		}



		std::vector<std::uint8_t> cast_to(
			const type::Array & to,
			const SourceLocation & location) {
			
			return to_array_of(to_type_code(**to.contains, location)); 
		}



		std::vector<std::uint8_t> cast_to(
			const auto & to,
			const SourceLocation & location) {
			throw cannot_cast(type::Any{}, to, location);
		}



		std::vector<std::uint8_t> to_type_code(
			const type::Type & to,
			const SourceLocation & location) {
			
			return to.visit([&] (auto & type) { 
				return cast_to(type, location);
			});
		}
	}



	InstructionBuffer copy_dynamic(
		const type::Type &,
		const type::Type & to,
		const SourceLocation & location) {
		return { inst::safe_copy(to_type_code(to, location)) };
	}
}