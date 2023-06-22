#pragma once
#include <string>
#include <ostream>
#include <functional>
#include "Indent.hxx"

namespace ltn::c::trans::cxx {

	struct PrimitiveType;

	using PrintPrimitiveMaker = std::function<void(const PrimitiveType & type, std::ostream & stream, Indent indent)>;
	
	struct PrimitiveType {
		std::string name;
		std::string data_type;
		std::string value_member;
		PrintPrimitiveMaker print_maker;
	};


	void generate_value_null(const PrimitiveType & type, std::ostream & stream, Indent indent);
	void generate_value_primitive(const PrimitiveType & type, std::ostream & stream, Indent indent);

	inline const auto primitive_types = std::vector {
		PrimitiveType {
			.name = "null",
			.data_type = "std::nullptr_t",
			.value_member = "n",
			.print_maker = generate_value_null,
		},
		PrimitiveType {
			.name = "bool",
			.data_type = "bool",
			.value_member = "b",
			.print_maker = generate_value_primitive,
		},
		PrimitiveType {
			.name = "char",
			.data_type = "std::uint8_t",
			.value_member = "c",
			.print_maker = generate_value_primitive,
		},
		PrimitiveType {
			.name = "int",
			.data_type = "std::int64_t",
			.value_member = "i",
			.print_maker = generate_value_primitive,
		},
		PrimitiveType {
			.name = "float",
			.data_type = "double",
			.value_member = "f",
			.print_maker = generate_value_primitive,
		},
	};
}