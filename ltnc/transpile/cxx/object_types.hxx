#pragma once
#include <array>
#include <ostream>
#include <functional>
#include "Indent.hxx"

namespace ltn::c::trans::cxx {
	using PrintObject = std::function<void(std::ostream &, std::string_view, std::string_view, Indent)>;

	struct ObjectType {
		std::string name;
		std::string data_type;
		std::string value_member;
		PrintObject print;
	};

	void generate_object(std::ostream & out, std::string_view name, std::string_view wrapped, Indent indent);
	void generate_stream_object(std::ostream & out, std::string_view name, std::string_view wrapped, Indent indent);
	
	const static auto object_types = std::vector {
		ObjectType {
			.name = "String", 
			.data_type = "std::string",
			.value_member = "str",
			.print = generate_object
		},
		ObjectType {
			.name = "Array",
			.data_type = "std::vector<Value>",
			.value_member = "arr",
			.print = generate_object
		},
		ObjectType {
			.name = "Tuple",
			.data_type = "std::vector<Value>",
			.value_member = "tup",
			.print = generate_object
		},
		ObjectType {
			.name = "OStream",
			.data_type = "std::ostream", 
			.value_member = "out",
			.print = generate_stream_object
		},
		ObjectType {
			.name = "IStream",
			.data_type = "std::istream", 
			.value_member = "in",
			.print = generate_stream_object
		},
	};

	void print_forward_decls(std::ostream & out, Indent indent, const std::vector<ObjectType> & objects);
	void print_objects(std::ostream & out, Indent indent, const std::vector<ObjectType> & objects);
}